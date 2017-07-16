/*
 * Copyright (C) 2002-2006, Mike Van Emmerik and Trent Waddington
 */

/***************************************************************************/ /**
 * \file    Boomerang.cpp
 * \brief   Command line processing for the Boomerang decompiler
 ******************************************************************************/

#include "Boomerang.h"

#include "boomerang/core/BinaryFileFactory.h"
#include "boomerang/util/Log.h"

#include "boomerang/codegen/CCodeGenerator.h"

#include "boomerang/db/BinaryImage.h"
#include "boomerang/db/SymTab.h"
#include "boomerang/db/prog.h"
#include "boomerang/db/proc.h"
#include "boomerang/db/project.h"
#include "boomerang/db/signature.h"

#include "boomerang/frontend/frontend.h"

// TODO: Move the Objective-C loader code to a more suitable place
#include "../../boomerang-loaders/machO/MachOBinaryLoader.h" // For Objective-C stuff


// For the -nG switch to disable the garbage collector
#ifdef HAVE_LIBGC
#include "boomerang/gc.h"
#endif

#include <QtCore/QDebug>
#include <ctime>


Boomerang *Boomerang::boomerang = nullptr;


Boomerang::Boomerang()
    : m_symbols(new SymTab)
    , m_progPath("./")
    , m_outputPath("./output/")
    , LogStream(stdout)
    , ErrStream(stderr)
    , m_currentProject(new Project)
{
}


Boomerang::~Boomerang()
{
    delete m_currentProject;
}


Log& Boomerang::log()
{
    return *m_logger;
}


SeparateLogger Boomerang::separate_log(const QString& v)
{
    return SeparateLogger(v);
}


Log& Boomerang::if_verbose_log(int verbosity_level)
{
    static NullLogger null_log;

    if (verbosity_level == 2) {
        return *m_logger;
    }

    if ((verbosity_level == 1) && VERBOSE) {
        return *m_logger;
    }
    else {
        return null_log;
    }
}


void Boomerang::setLogger(Log *l)
{
    delete m_logger;
    m_logger = l;
}


ICodeGenerator *Boomerang::getHLLCode(UserProc *p)
{
    return new CCodeGenerator(p);
}


void Boomerang::helpcmd() const
{
    QTextStream c_out(stdout);

    // Column 98 of this source file is column 80 of output (don't use tabs)
    //  ____.____1____.____2____.____3____.____4____.____5____.____6____.____7____.____8
    c_out <<
        "Available commands (for use with -k):\n"
        "  decode                             : Loads and decodes the specified binary.\n"
        "  decompile [proc]                   : Decompiles the program or specified proc.\n"
        "  codegen [cluster]                  : Generates code for the program or a\n"
        "                                       specified cluster.\n"
        "  move proc <proc> <cluster>         : Moves the specified proc to the specified\n"
        "                                       cluster.\n"
        "  move cluster <cluster> <parent>    : Moves the specified cluster to the\n"
        "                                       specified parent cluster.\n"
        "  add cluster <cluster> [parent]     : Adds a new cluster to the root/specified\n"
        "                                       cluster.\n"
        "  delete cluster <cluster>           : Deletes an empty cluster.\n"
        "  rename proc <proc> <newname>       : Renames the specified proc.\n"
        "  rename cluster <cluster> <newname> : Renames the specified cluster.\n"
        "  info prog                          : Print info about the program.\n"
        "  info cluster <cluster>             : Print info about a cluster.\n"
        "  info proc <proc>                   : Print info about a proc.\n"
        "  print <proc>                       : Print the RTL for a proc.\n"
        "  help                               : This help.\n"
        "  exit                               : Quit the shell.\n";
}


/**
 * Creates a directory and tests it.
 *
 * \param dir The name of the directory.
 *
 * \retval true The directory is valid.
 * \retval false The directory is invalid.
 */
bool createDirectory(const QString& dir)
{
    QFileInfo dir_fi(dir);
    QString   abspath = dir_fi.absolutePath();

    return QDir::root().mkpath(abspath);
}


enum CommandType
{
    CT_unknown   = -1,
    CT_decode    = 1,
    CT_load      = 2,
    CT_save      = 3,
    CT_decompile = 4,
    CT_codegen   = 5,
    CT_move      = 6,
    CT_add       = 7,
    CT_delete    = 8,
    CT_rename    = 9,
    CT_info      = 10,
    CT_print     = 11,
    CT_exit      = 12,
    CT_help      = 13
};

static CommandType commandNameToID(const QString& _cmd)
{
    if (_cmd == "decode") {
        return CT_decode;
    }

    if (_cmd == "load") {
        return CT_load;
    }

    if (_cmd == "save") {
        return CT_save;
    }

    if (_cmd == "decompile") {
        return CT_decompile;
    }

    if (_cmd == "codegen") {
        return CT_codegen;
    }

    if (_cmd == "move") {
        return CT_move;
    }

    if (_cmd == "add") {
        return CT_add;
    }

    if (_cmd == "delete") {
        return CT_delete;
    }

    if (_cmd == "rename") {
        return CT_rename;
    }

    if (_cmd == "info") {
        return CT_info;
    }

    if (_cmd == "print") {
        return CT_print;
    }

    if ((_cmd == "exit") || (_cmd == "quit")) {
        return CT_exit;
    }

    if (_cmd == "help") {
        return CT_help;
    }

    return CT_unknown;
}


int Boomerang::processCommand(QStringList& args)
{
    static Prog *prog = nullptr;
    QTextStream err_stream(stderr);
    QTextStream out_stream(stdout);

    if (args.isEmpty()) {
        err_stream << "not enough arguments\n";
        return 1;
    }

    CommandType command = commandNameToID(args[0]);

    switch (command)
    {
    case CT_decode:
        {
            if (args.size() < 2) {
                err_stream << "Not enough arguments for cmd\n";
                return 1;
            }

            Prog *p = loadAndDecode(args[1]);

            if (p == nullptr) {
                err_stream << "failed to load " << args[1] << "\n";
                return 1;
            }

            prog = p;
            break;
        }

    case CT_load:
        {
            if (args.size() < 2) {
                err_stream << "not enough arguments for cmd\n";
                return 1;
            }

            QString fname = args[1];
            err_stream << "Cannot load " << fname << ": Operation not implemented.\n";
            break;
        }

    case CT_save:

        if (prog == nullptr) {
            err_stream << "need to load or decode before save!\n";
            return 1;
        }

        err_stream << "Cannot save: Operation not implemented.\n";
        break;

    case CT_decompile:

        if (prog == nullptr) {
            err_stream << "no valid Prog object !\n";
            return 1;
        }

        if (args.size() > 1) {
            Function *proc = prog->findProc(args[1]);

            if (proc == nullptr) {
                err_stream << "cannot find proc " << args[1] << "\n";
                return 1;
            }

            if (proc->isLib()) {
                err_stream << "cannot decompile a lib proc\n";
                return 1;
            }

            int indent = 0;
            assert(dynamic_cast<UserProc *>(proc) != nullptr);
            ((UserProc *)proc)->decompile(new ProcList, indent);
        }
        else {
            prog->decompile();
        }

        break;

    case CT_codegen:

        if (prog == nullptr) {
            err_stream << "no valid Prog object !\n";
            return 1;
        }

        if (args.size() > 1) {
            Module *cluster = prog->findModule(args[1]);

            if (cluster == nullptr) {
                err_stream << "cannot find cluster " << args[1] << "\n";
                return 1;
            }

            prog->generateCode(cluster);
        }
        else {
            prog->generateCode();
        }

        break;

    case CT_move:

        if (prog == nullptr) {
            err_stream << "no valid Prog object !\n";
            return 1;
        }

        if (args.size() <= 1) {
            err_stream << "not enough arguments for cmd\n";
            return 1;
        }

        if (args[1] == "proc") {
            if (args.size() < 4) {
                err_stream << "not enough arguments for cmd\n";
                return 1;
            }

            Function *proc = prog->findProc(args[2]);

            if (proc == nullptr) {
                err_stream << "cannot find proc " << args[2] << "\n";
                return 1;
            }

            Module *cluster = prog->findModule(args[3]);

            if (cluster == nullptr) {
                err_stream << "cannot find cluster " << args[3] << "\n";
                return 1;
            }

            proc->setParent(cluster);
        }
        else if (!args[1].compare("cluster")) {
            if (args.size() <= 3) {
                err_stream << "not enough arguments for cmd\n";
                return 1;
            }

            Module *cluster = prog->findModule(args[2]);

            if (cluster == nullptr) {
                err_stream << "cannot find cluster " << args[2] << "\n";
                return 1;
            }

            Module *parent = prog->findModule(args[3]);

            if (parent == nullptr) {
                err_stream << "cannot find cluster " << args[3] << "\n";
                return 1;
            }

            parent->addChild(cluster);
        }
        else {
            err_stream << "don't know how to move a " << args[1] << "\n";
            return 1;
        }

        break;

    case CT_add:

        if (prog == nullptr) {
            err_stream << "no valid Prog object !\n";
            return 1;
        }

        if (args.size() <= 1) {
            err_stream << "not enough arguments for cmd\n";
            return 1;
        }

        if (args[1] == "cluster") {
            if (args.size() <= 2) {
                err_stream << "not enough arguments for cmd\n";
                return 1;
            }

            Module *cluster = new Module(args[2], prog, prog->getFrontEnd());

            if (cluster == nullptr) {
                err_stream << "cannot create cluster " << args[2] << "\n";
                return 1;
            }

            Module *parent = prog->getRootCluster();

            if (args.size() > 3) {
                parent = prog->findModule(args[3]);

                if (cluster == nullptr) {
                    err_stream << "cannot find cluster " << args[3] << "\n";
                    return 1;
                }
            }

            parent->addChild(cluster);
        }
        else {
            err_stream << "don't know how to add a " << args[1] << "\n";
            return 1;
        }

        break;

    case CT_delete:

        if (prog == nullptr) {
            err_stream << "no valid Prog object !\n";
            return 1;
        }

        if (args.size() <= 1) {
            err_stream << "not enough arguments for cmd\n";
            return 1;
        }

        if (!args[1].compare("cluster")) {
            if (args.size() <= 2) {
                err_stream << "not enough arguments for cmd\n";
                return 1;
            }

            Module *cluster = prog->findModule(args[2]);

            if (cluster == nullptr) {
                err_stream << "cannot find cluster " << args[2] << "\n";
                return 1;
            }

            if (cluster->hasChildren() || (cluster == prog->getRootCluster())) {
                err_stream << "cluster " << args[2] << " is not empty\n";
                return 1;
            }

            if (prog->isModuleUsed(cluster)) {
                err_stream << "cluster " << args[2] << " is not empty\n";
                return 1;
            }

            QFile::remove(cluster->getOutPath("xml"));
            QFile::remove(cluster->getOutPath("c"));
            assert(cluster->getUpstream());
            cluster->getUpstream()->removeChild(cluster);
        }
        else {
            err_stream << "don't know how to delete a " << args[1] << "\n";
            return 1;
        }

        break;

    case CT_rename:

        if (prog == nullptr) {
            err_stream << "no valid Prog object !\n";
            return 1;
        }

        if (args.size() <= 1) {
            err_stream << "not enough arguments for cmd\n";
            return 1;
        }

        if (args[1] == "proc") {
            if (args.size() <= 3) {
                err_stream << "not enough arguments for cmd\n";
                return 1;
            }

            Function *proc = prog->findProc(args[2]);

            if (proc == nullptr) {
                err_stream << "cannot find proc " << args[2] << "\n";
                return 1;
            }

            Function *nproc = prog->findProc(args[3]);

            if (nproc != nullptr) {
                err_stream << "proc " << args[3] << " already exists\n";
                return 1;
            }

            proc->setName(args[3]);
        }
        else if (args[1] == "cluster") {
            if (args.size() <= 3) {
                err_stream << "not enough arguments for cmd\n";
                return 1;
            }

            Module *cluster = prog->findModule(args[2]);

            if (cluster == nullptr) {
                err_stream << "cannot find cluster " << args[2] << "\n";
                return 1;
            }

            Module *ncluster = prog->findModule(args[3]);

            if (ncluster == nullptr) {
                err_stream << "cluster " << args[3] << " already exists\n";
                return 1;
            }

            cluster->setName(args[3]);
        }
        else {
            err_stream << "don't know how to rename a " << args[1] << "\n";
            return 1;
        }

        break;

    case CT_info:

        if (prog == nullptr) {
            err_stream << "no valid Prog object !\n";
            return 1;
        }

        if (args.size() <= 1) {
            err_stream << "not enough arguments for cmd\n";
            return 1;
        }

        if (args[1] == "prog") {
            out_stream << "prog " << prog->getName() << ":\n";
            out_stream << "\tclusters:\n";
            prog->getRootCluster()->printTree(out_stream);
            out_stream << "\n\tlibprocs:\n";

            // TODO: print module name before function's ?
            for (const Module *module : *prog) {
                for (Function *func : *module) {
                    if (func->isLib()) {
                        out_stream << "\t\t" << func->getName() << "\n";
                    }
                }
            }

            out_stream << "\n\tuserprocs:\n";

            for (const Module *module : *prog) {
                for (Function *func : *module) {
                    if (!func->isLib()) {
                        out_stream << "\t\t" << func->getName() << "\n";
                    }
                }
            }

            out_stream << "\n";

            return 0;
        }
        else if (args[1] == "cluster") {
            if (args.size() <= 2) {
                err_stream << "not enough arguments for cmd\n";
                return 1;
            }

            Module *cluster = prog->findModule(args[2]);

            if (cluster == nullptr) {
                err_stream << "cannot find cluster " << args[2] << "\n";
                return 1;
            }

            out_stream << "cluster " << cluster->getName() << ":\n";

            if (cluster->getUpstream()) {
                out_stream << "\tparent = " << cluster->getUpstream()->getName() << "\n";
            }
            else {
                out_stream << "\troot cluster.\n";
            }

            out_stream << "\tprocs:\n";

            for (Function *f : *cluster) {
                out_stream << "\t\t" << f->getName() << "\n";
            }

            out_stream << "\n";

            return 0;
        }
        else if (args[1] == "proc") {
            if (args.size() <= 2) {
                err_stream << "not enough arguments for cmd\n";
                return 1;
            }

            Function *proc = prog->findProc(args[2]);

            if (proc == nullptr) {
                err_stream << "cannot find proc " << args[2] << "\n";
                return 1;
            }

            out_stream << "proc " << proc->getName() << ":\n";
            out_stream << "\tbelongs to cluster " << proc->getParent()->getName() << "\n";
            out_stream << "\tnative address " << proc->getNativeAddress() << "\n";

            if (proc->isLib()) {
                out_stream << "\tis a library proc.\n";
            }
            else {
                out_stream << "\tis a user proc.\n";
                UserProc *p = (UserProc *)proc;

                if (p->isDecoded()) {
                    out_stream << "\thas been decoded.\n";
                }

                // if (p->isAnalysed())
                //    out_stream << "\thas been analysed.\n";
            }

            out_stream << "\n";

            return 0;
        }
        else {
            err_stream << "don't know how to print info about a " << args[1] << "\n";
            return 1;
        }

    // no break needed all branches return
    case CT_print:
        {
            if (prog == nullptr) {
                err_stream << "no valid Prog object !\n";
                return 1;
            }

            if (args.size() < 2) {
                err_stream << "not enough arguments for cmd\n";
                return 1;
            }

            Function *proc = prog->findProc(args[1]);

            if (proc == nullptr) {
                err_stream << "cannot find proc " << args[1] << "\n";
                return 1;
            }

            if (proc->isLib()) {
                err_stream << "cannot print a libproc.\n";
                return 1;
            }

            ((UserProc *)proc)->print(out_stream);
            out_stream << "\n";
            return 0;
        }

    case CT_exit:
        return 2;

    case CT_help:
        helpcmd();
        return 0;

    default:
        err_stream << "unknown cmd " << args[0] << ".\n";
        return 1;
    }

    return 0;
}


void Boomerang::setProgPath(const QString& p)
{
    m_progPath   = p + "/";
    m_outputPath = m_progPath + "/output/";    // Default output path (can be overridden with -o below)
}


void Boomerang::setPluginPath(const QString& p)
{
    BinaryFileFactory::setPluginsPath(qPrintable(p));
}


bool Boomerang::setOutputDirectory(const QString& path)
{
    m_outputPath = path;

    if (!m_outputPath.endsWith(QDir::separator())) {
        m_outputPath += QDir::separator();
    }

    // Create the output directory, if needed
    if (!createDirectory(path)) {
        qWarning() << "Warning! Could not create path " << m_outputPath << "!\n";
        return false;
    }

    if (m_logger == nullptr) {
        setLogger(new FileLogger());
    }

    return true;
}


void Boomerang::objcDecode(const std::map<QString, ObjcModule>& modules, Prog *prog)
{
    LOG_VERBOSE(1) << "Adding Objective-C information to Prog.\n";
    Module *root = prog->getRootCluster();

    for (auto& modules_it : modules) {
        const ObjcModule& mod     = (modules_it).second;
        Module            *module = prog->getOrInsertModule(mod.name);
        root->addChild(module);
        LOG_VERBOSE(1) << "\tModule: " << mod.name << "\n";
        ClassModFactory class_fact;

        for (auto& elem : mod.classes) {
            const ObjcClass& c   = (elem).second;
            Module           *cl = prog->getOrInsertModule(mod.name, class_fact);
            root->addChild(cl);
            LOG_VERBOSE(1) << "\t\tClass: " << c.name << "\n";

            for (auto& _it2 : c.methods) {
                const ObjcMethod& m = (_it2).second;
                // TODO: parse :'s in names
                QString  method_name = m.name + "_" + m.types;
                Function *existing   = prog->findProc(method_name);

                if (existing) {
                    assert(!"Name clash in objc processor ?");
                    continue;
                }

                Function *p = cl->getOrInsertFunction(method_name, m.addr);
                p->setSignature(Signature::instantiate(prog->getFrontEndId(), CallConv::C, method_name));
                // TODO: decode types in m.types
                LOG_VERBOSE(1) << "\t\t\tMethod: " << m.name << "\n";
            }
        }
    }

    LOG_VERBOSE(1) << "\n";
}


Prog *Boomerang::loadAndDecode(const QString& fname, const char *pname)
{
    QTextStream q_cout(stdout);

    q_cout << "loading...\n";
    Prog      *prog = new Prog(fname);
    IFrontEnd *fe   = IFrontEnd::create(fname, prog);

    if (fe == nullptr) {
        LOG_STREAM(LL_Default) << "failed.\n";
        return nullptr;
    }

    prog->setFrontEnd(fe);

    // Add symbols from -s switch(es)
    for (const std::pair<Address, QString>& elem : symbols) {
        fe->addSymbol(elem.first, elem.second);
    }

    fe->readLibraryCatalog(); // Needed before readSymbolFile()

    for (auto& elem : m_symbolFiles) {
        q_cout << "reading symbol file " << elem << "\n";
        prog->readSymbolFile(elem);
    }

    // Entry points from -e (and -E) switch(es)
    for (auto& elem : m_entryPoints) {
        q_cout << "decoding specified entrypoint " << elem << "\n";
        prog->decodeEntryPoint(elem);
    }

    if (m_entryPoints.size() == 0) { // no -e or -E given
        if (decodeMain) {
            q_cout << "decoding entry point...\n";
        }

        fe->decode(prog, decodeMain, pname);

        if (!noDecodeChildren) {
            // this causes any undecoded userprocs to be decoded
            q_cout << "decoding anything undecoded...\n";
            fe->decode(prog, Address::INVALID);
        }
    }

    q_cout << "finishing decode...\n";
    prog->finishDecode();

    Boomerang::get()->alertEndDecode();

    q_cout << "found " << prog->getNumProcs() << " procs\n";

    // GK: The analysis which was performed was not exactly very "analysing", and so it has been moved to
    // prog::finishDecode, UserProc::assignProcsToCalls and UserProc::finalSimplify
    // std::cout << "analysing...\n";
    // prog->analyse();

    if (generateSymbols) {
        prog->printSymbolsToFile();
    }

    if (generateCallGraph) {
        prog->printCallGraph();
        prog->printCallGraphXML();
    }

    return prog;
}


int Boomerang::decompile(const QString& fname, const char *pname)
{
    Prog   *prog = nullptr;
    time_t start;

    time(&start);

    if (m_logger == nullptr) {
        setLogger(new FileLogger());
    }

    if (loadBeforeDecompile) {
        LOG_STREAM() << "loading persisted state...\n";
        assert(false);
    }
    else {
        prog = loadAndDecode(fname, pname);

        if (prog == nullptr) {
            return 1;
        }
    }

    if (saveBeforeDecompile) {
        assert(false);
    }

    if (stopBeforeDecompile) {
        return 0;
    }

    LOG_STREAM() << "decompiling...\n";
    prog->decompile();

    if (!dotFile.isEmpty()) {
        prog->generateDotFile();
    }

    if (printAST) {
        LOG_STREAM() << "printing AST...\n";

        for (const Module *module : *prog) {
            for (Function *func : *module) {
                if (!func->isLib()) {
                    UserProc *u = (UserProc *)func;
                    u->getCFG()->compressCfg();
                    u->printAST();
                }
            }
        }
    }

    QTextStream q_cout(stdout);
    q_cout << "generating code...\n";
    prog->generateCode();

    q_cout << "output written to " << m_outputPath << prog->getRootCluster()->getName() << "\n";

    time_t end;
    time(&end);
    int hours = (int)((end - start) / 60 / 60);
    int mins  = (int)((end - start) / 60 - hours * 60);
    int secs  = (int)((end - start) - (hours * 60 * 60) - (mins * 60));
    q_cout << "completed in ";

    if (hours) {
        q_cout << hours << " hours ";
    }

    if (hours || mins) {
        q_cout << mins << " mins ";
    }

    q_cout << secs << " sec" << (secs == 1 ? "" : "s") << ".\n";
    delete prog;
    return 0;
}


void Boomerang::miniDebugger(UserProc *p, const char *description)
{
    QTextStream q_cout(stdout);
    QTextStream q_cin(stdin);

    q_cout << "decompiling " << p->getName() << ": " << description << "\n";
    QString stopAt;
    static std::set<Instruction *> watches;

    if (stopAt.isEmpty() || !p->getName().compare(stopAt)) {
        // This is a mini command line debugger.  Feel free to expand it.
        for (auto const& watche : watches) {
            (watche)->print(q_cout);
            q_cout << "\n";
        }

        q_cout << " <press enter to continue> \n";
        QString line;

        while (1) {
            line.clear();
            q_cin >> line;

            if (line.startsWith("print")) {
                p->print(q_cout);
            }
            else if (line.startsWith("fprint")) {
                QFile tgt("out.proc");

                if (tgt.open(QFile::WriteOnly)) {
                    QTextStream of(&tgt);
                    p->print(of);
                }
            }
            else if (line.startsWith("run ")) {
                QStringList parts = line.trimmed().split(" ", QString::SkipEmptyParts);

                if (parts.size() > 1) {
                    stopAt = parts[1];
                }

                break;
            }
            else if (line.startsWith("watch ")) {
                QStringList parts = line.trimmed().split(" ", QString::SkipEmptyParts);

                if (parts.size() > 1) {
                    int           n = parts[1].toInt();
                    StatementList stmts;
                    p->getStatements(stmts);
                    StatementList::iterator it;

                    for (it = stmts.begin(); it != stmts.end(); it++) {
                        if ((*it)->getNumber() == n) {
                            watches.insert(*it);
                            q_cout << "watching " << *it << "\n";
                        }
                    }
                }
            }
            else {
                break;
            }
        }
    }
}


Boomerang *Boomerang::get()
{
    if (!boomerang) {
        boomerang = new Boomerang();
    }

    return boomerang;
}


IBinaryImage *Boomerang::getImage()
{
    assert(m_currentProject != nullptr);
    return m_currentProject->getOrCreateImage();
}


IBinarySymbolTable *Boomerang::getSymbols()
{
    return m_symbols;
}


void Boomerang::alertDecompileDebugPoint(UserProc *p, const char *description)
{
    if (stopAtDebugPoints) {
        miniDebugger(p, description);
    }

    for (Watcher *elem : m_watchers) {
        elem->alertDecompileDebugPoint(p, description);
    }
}


QTextStream& Boomerang::getLogStream(int level)
{
    if (level >= LL_Error) {
        return ErrStream;
    }

    return LogStream;
}


QString Boomerang::filename() const
{
    return "";
}


const char *Boomerang::getVersionStr()
{
    return BOOMERANG_VERSION;
}
