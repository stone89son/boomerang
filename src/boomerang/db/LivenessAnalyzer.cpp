#pragma region License
/*
 * This file is part of the Boomerang Decompiler.
 *
 * See the file "LICENSE.TERMS" for information on usage and
 * redistribution of this file, and for a DISCLAIMER OF ALL
 * WARRANTIES.
 */
#pragma endregion License
#include "LivenessAnalyzer.h"


#include "boomerang/db/statements/PhiAssign.h"
#include "boomerang/db/proc/UserProc.h"
#include "boomerang/db/BasicBlock.h"
#include "boomerang/db/RTL.h"
#include "boomerang/util/LocationSet.h"
#include "boomerang/util/ConnectionGraph.h"

#include "boomerang/db/exp/RefExp.h"
#include "boomerang/core/Boomerang.h"


/**
 * Check for overlap of liveness between the currently live locations (liveLocs) and the set of locations in ls
 * Also check for type conflicts if DFA_TYPE_ANALYSIS
 * This is a helper function that is not directly declared in the BasicBlock class
 */
void checkForOverlap(LocationSet& liveLocs, LocationSet& ls, ConnectionGraph& ig, UserProc *)
{
    // For each location to be considered
    for (SharedExp exp : ls) {
        if (!exp->isSubscript()) {
            continue; // Only interested in subscripted vars
        }

        assert(std::dynamic_pointer_cast<RefExp>(exp) != nullptr);

        auto refexp = std::static_pointer_cast<RefExp>(exp);
        // Interference if we can find a live variable which differs only in the reference
        SharedExp dr;

        if (liveLocs.findDifferentRef(refexp, dr)) {
            assert(dr->access<RefExp>()->getDef() != nullptr);
            assert(exp->access<RefExp>()->getDef() != nullptr);
            // We have an interference between r and dr. Record it
            ig.connect(refexp, dr);

            if (SETTING(debugLiveness)) {
                LOG_VERBOSE("Interference of %1 with %2", dr, refexp);
            }
        }

        // Add the uses one at a time. Note: don't use makeUnion, because then we don't discover interferences
        // from the same statement, e.g.  blah := r24{2} + r24{3}
        liveLocs.insert(exp);
    }
}


bool LivenessAnalyzer::calcLiveness(BasicBlock *bb, ConnectionGraph& ig, UserProc *myProc)
{
    // Start with the liveness at the bottom of the BB
    LocationSet liveLocs, phiLocs;

    getLiveOut(bb, liveLocs, phiLocs);
    // Do the livensses that result from phi statements at successors first.
    // FIXME: document why this is necessary
    checkForOverlap(liveLocs, phiLocs, ig, myProc);

    // For each RTL in this BB
    RTLList::reverse_iterator rit;

    if (bb->getRTLs()) { // this can be nullptr
        for (rit = bb->getRTLs()->rbegin(); rit != bb->getRTLs()->rend(); ++rit) {
            std::list<Statement *>::reverse_iterator sit;

            // For each statement this RTL
            for (sit = (*rit)->rbegin(); sit != (*rit)->rend(); ++sit) {
                Statement   *s = *sit;
                LocationSet defs;
                s->getDefinitions(defs);
                // The definitions don't have refs yet
                defs.addSubscript(s /* , myProc->getCFG() */);

                // Definitions kill uses. Now we are moving to the "top" of statement s
                liveLocs.makeDiff(defs);

                // Phi functions are a special case. The operands of phi functions are uses, but they don't interfere
                // with each other (since they come via different BBs). However, we don't want to put these uses into
                // liveLocs, because then the livenesses will flow to all predecessors. Only the appropriate livenesses
                // from the appropriate phi parameter should flow to the predecessor. This is done in getLiveOut()
                if (s->isPhi()) {
                    continue;
                }

                // Check for livenesses that overlap
                LocationSet uses;
                s->addUsedLocs(uses);
                checkForOverlap(liveLocs, uses, ig, myProc);

                if (SETTING(debugLiveness)) {
                    LOG_MSG(" ## liveness: at top of %1, liveLocs is %2", s, liveLocs.prints());
                }
            }
        }
    }

    // liveIn is what we calculated last time
    if (!(liveLocs == m_liveIn[bb])) {
        m_liveIn[bb] = liveLocs;
        return true; // A change
    }

    // No change
    return false;
}


void LivenessAnalyzer::getLiveOut(BasicBlock *bb, LocationSet& liveout, LocationSet& phiLocs)
{
    Cfg *cfg = static_cast<UserProc *>(bb->getFunction())->getCFG();

    liveout.clear();

    for (BasicBlock *currBB : bb->getSuccessors()) {
        // First add the non-phi liveness
        liveout.makeUnion(m_liveIn[currBB]); // add successor liveIn to this liveout set.

        // The first RTL will have the phi functions, if any
        if ((currBB->getRTLs() == nullptr) || (currBB->getRTLs()->size() == 0)) {
            continue;
        }

        RTL *phiRTL = currBB->getRTLs()->front().get();
        assert(phiRTL);

        for (Statement *st : *phiRTL) {
            // Only interested in phi assignments. Note that it is possible that some phi assignments have been
            // converted to ordinary assignments. So the below is a continue, not a break.
            if (!st->isPhi()) {
                continue;
            }

            PhiAssign *pa = dynamic_cast<PhiAssign *>(st);

            for (const auto& v : pa->getDefs()) {
                if (!cfg->hasBB(v.first)) {
                    LOG_WARN("Someone removed the BB that defined the PHI! Need to update PhiAssign defs");
                }
            }

            // Get the jth operand to the phi function; it has a use from BB *this
            // assert(j>=0);
            Statement *def = pa->getStmtAt(bb);

            if (!def) {
                std::set<BasicBlock *> tried { bb };
                std::deque<BasicBlock *> to_visit(
                    bb->getPredecessors().begin(),
                    bb->getPredecessors().end());

                // TODO: this looks like a hack ?  but sometimes PhiAssign has value which is defined in parent of
                // 'this'
                //  BB1 1  - defines r20
                //  BB2 33 - transfers control to BB3
                //  BB3 40 - r10 = phi { 1 }
                while (!to_visit.empty()) {
                    BasicBlock *pbb = to_visit.back();

                    if (tried.find(pbb) != tried.end()) {
                        to_visit.pop_back();
                        continue;
                    }

                    def = pa->getStmtAt(pbb);

                    if (def) {
                        break;
                    }

                    tried.insert(pbb);
                    to_visit.pop_back();

                    for (BasicBlock *pred : pbb->getPredecessors()) {
                        if (tried.find(pred) != tried.end()) { // already tried
                            continue;
                        }

                        to_visit.push_back(pred);
                    }
                }
            }

            SharedExp ref = RefExp::get(pa->getLeft()->clone(), def);
            assert(def);
            liveout.insert(ref);
            phiLocs.insert(ref);

            if (SETTING(debugLiveness)) {
                LOG_MSG(" ## Liveness: adding %1 due due to ref to phi %2 in BB at %3",
                        ref, st, bb->getLowAddr());
            }
        }
    }
}