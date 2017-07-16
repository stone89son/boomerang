#pragma once

/*
 * machine/sparc/sparc.h - Emulator interface file
 *
 * Automatically generated by genemu 0.61 on Tue Mar 19 18:21:35 2002 from:
 *   machine/sparc/sparc-core.spec            (Wed Nov 28 09:33:18 2001)
 *   machine/sparc/sparc.ssl                  (Wed Nov 28 09:33:21 2001)
 */

#include <stdlib.h>

typedef signed char          sint8_t;
typedef signed short         sint16_t;
typedef signed int           sint32_t;
typedef signed long long     sint64_t;
typedef unsigned char        uint8_t;
typedef unsigned short       uint16_t;
typedef unsigned int         uint32_t;
typedef unsigned long long   uint64_t;
typedef float                float32_t;
typedef double               float64_t;
typedef long double          float128_t;
typedef long double          NO_SUCH_TYPE; /* temporary copout */

#ifndef HAVE_disasm_fmt_t
#define HAVE_disasm_fmt_t

typedef struct
{
    char *addrfmt;
    char *hexfmt;
    int  hexwidth, hexlen;
    int  opnamelen;
    int  operandlen;
    bool showHex;
    bool showSymbols;
} disasm_fmt_t;

#endif /* !HAVE_disasm_fmt_t */

extern disasm_fmt_t defDisasmFmt;

/*
 * Low-level disassembly function. Given mem relative pc,
 * disassembles one instruction, returning the operands as a string in
 * params, and setting name (if not nullptr) to the operation name.
 * Returns the pc of the immediately following instruction
 */
int disassembleInstruction(int pc, char *params, size_t paramlen, char **name);

/*
 * Public disassembly function. Given mem relative pc, disassembles
 * the instruction and stores a human-readable representation in buf, with the
 * formatting determined by fmt. Returns the pc of the following instruction.
 */
int sprintDisassembleInst(int pc, char *buf, int buflen, disasm_fmt_t& fmt = defDisasmFmt);

/* Globals */

/* Zero if debugging should be turned off, non-zero otherwise */
extern int debug;

/* count of total instructions executed to date */
extern long int icount;

/* Functions */

/*
 * Low-level function that executes the instruction at the given pc, and returns
 * the pc of the immediately following instruction (this is not necessarily the
 * next instruction to be executed). You don't usually need to use this directly
 */
uint32_t execute(uint32_t pc);

/*
 * Public single-step function. Executes the instruction at the current pc, and
 * updates the pc to point to the next instruction for execution.
 */
void executeOneInstruction();

/*
 * Callback hook for traps. cond is true if the trap should execute, and the
 * trap number is given in trap.
 */
void doTrap(int trap);

/*
 * Various register dumping procedures.
 */
void dumpControlRegisters(FILE *f);
void dumpMainRegisters(FILE *f);
void dumpFloatRegisters(FILE *f);
void dumpAllRegisters(FILE *f);

/* Register structure */
struct RegisterFile
{
    sint32_t rd[32];
    union
    {
        struct
        {
            union
            {
                struct
                {
                    float32_t r_f0;
                    float32_t r_f1;
                }

                          r_f0to1_str;

                float64_t r_f0to1;
            }

            r_f0to1_un;

            union
            {
                struct
                {
                    float32_t r_f2;
                    float32_t r_f3;
                }

                          r_f2to3_str;

                float64_t r_f2to3;
            }

            r_f2to3_un;
        }

                   r_f0to3_str;

        float128_t r_f0to3;
    }

             r_f0to3_un;

    union
    {
        struct
        {
            union
            {
                struct
                {
                    float32_t r_f4;
                    float32_t r_f5;
                }

                          r_f4to5_str;

                float64_t r_f4to5;
            }

            r_f4to5_un;

            union
            {
                struct
                {
                    float32_t r_f6;
                    float32_t r_f7;
                }

                          r_f6to7_str;

                float64_t r_f6to7;
            }

            r_f6to7_un;
        }

                   r_f4to7_str;

        float128_t r_f4to7;
    }

             r_f4to7_un;

    union
    {
        struct
        {
            union
            {
                struct
                {
                    float32_t r_f8;
                    float32_t r_f9;
                }

                          r_f8to9_str;

                float64_t r_f8to9;
            }

            r_f8to9_un;

            union
            {
                struct
                {
                    float32_t r_f10;
                    float32_t r_f11;
                }

                          r_f10to11_str;

                float64_t r_f10to11;
            }

            r_f10to11_un;
        }

                   r_f8to11_str;

        float128_t r_f8to11;
    }

             r_f8to11_un;

    union
    {
        struct
        {
            union
            {
                struct
                {
                    float32_t r_f12;
                    float32_t r_f13;
                }

                          r_f12to13_str;

                float64_t r_f12to13;
            }

            r_f12to13_un;

            union
            {
                struct
                {
                    float32_t r_f14;
                    float32_t r_f15;
                }

                          r_f14to15_str;

                float64_t r_f14to15;
            }

            r_f14to15_un;
        }

                   r_f12to15_str;

        float128_t r_f12to15;
    }

             r_f12to15_un;

    union
    {
        struct
        {
            union
            {
                struct
                {
                    float32_t r_f16;
                    float32_t r_f17;
                }

                          r_f16to17_str;

                float64_t r_f16to17;
            }

            r_f16to17_un;

            union
            {
                struct
                {
                    float32_t r_f18;
                    float32_t r_f19;
                }

                          r_f18to19_str;

                float64_t r_f18to19;
            }

            r_f18to19_un;
        }

                   r_f16to19_str;

        float128_t r_f16to19;
    }

             r_f16to19_un;

    union
    {
        struct
        {
            union
            {
                struct
                {
                    float32_t r_f20;
                    float32_t r_f21;
                }

                          r_f20to21_str;

                float64_t r_f20to21;
            }

            r_f20to21_un;

            union
            {
                struct
                {
                    float32_t r_f22;
                    float32_t r_f23;
                }

                          r_f22to23_str;

                float64_t r_f22to23;
            }

            r_f22to23_un;
        }

                   r_f20to23_str;

        float128_t r_f20to23;
    }

             r_f20to23_un;

    union
    {
        struct
        {
            union
            {
                struct
                {
                    float32_t r_f24;
                    float32_t r_f25;
                }

                          r_f24to25_str;

                float64_t r_f24to25;
            }

            r_f24to25_un;

            union
            {
                struct
                {
                    float32_t r_f26;
                    float32_t r_f27;
                }

                          r_f26to27_str;

                float64_t r_f26to27;
            }

            r_f26to27_un;
        }

                   r_f24to27_str;

        float128_t r_f24to27;
    }

             r_f24to27_un;

    union
    {
        struct
        {
            union
            {
                struct
                {
                    float32_t r_f28;
                    float32_t r_f29;
                }

                          r_f28to29_str;

                float64_t r_f28to29;
            }

            r_f28to29_un;

            union
            {
                struct
                {
                    float32_t r_f30;
                    float32_t r_f31;
                }

                          r_f30to31_str;

                float64_t r_f30to31;
            }

            r_f30to31_un;
        }

                   r_f28to31_str;

        float128_t r_f28to31;
    }

             r_f28to31_un;

    sint8_t  r_AF;
    sint8_t  r_CF;
    sint8_t  r_CTI;
    sint32_t r_CWP;
    sint8_t  r_FGF;
    sint8_t  r_FLF;
    sint32_t r_FSR;
    sint8_t  r_FZF;
    sint32_t r_NEXT;
    sint8_t  r_NF;
    sint8_t  r_OF;
    sint32_t r_PSR;
    sint32_t r_TBR;
    sint32_t r_WIM;
    sint32_t r_Y;
    sint8_t  r_ZF;
    sint32_t r_npc;
    sint32_t r_pc;
};

extern RegisterFile regs;

extern char *mem;
