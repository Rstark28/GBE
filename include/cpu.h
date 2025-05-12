/**
 * CPU (Sharp LR35902) implementation header
 *
 * Implementation Tasks:
 * 1. Registers and flags
 * 2. Instruction fetch-decode-execute loop
 * 3. Basic instructions (NOP, LD, INC/DEC)
 * 4. ALU operations
 * 5. Jumps and calls
 * 6. Stack operations
 * 7. Cycle-accurate timing
 * 8. HALT behavior
 */

#ifndef GBE_CPU_H
#define GBE_CPU_H

#include "core.h"

// CPU registers
typedef struct
{
        // 8-bit registers
        u8 a; // Accumulator
        u8 f; // Flags
        u8 b;
        u8 c;
        u8 d;
        u8 e;
        u8 h;
        u8 l;

        // 16-bit registers
        u16 pc; // Program Counter
        u16 sp; // Stack Pointer

        // Flags
        bool z; // Zero flag
        bool n; // Subtract flag
        bool h; // Half carry flag
        bool c; // Carry flag

        // CPU state
        bool halted;
        bool ime; // Interrupt Master Enable
        int cycles;
} GBE_CPU;

// Function declarations
void cpu_init(GBE_CPU *cpu);
void cpu_step(GBE_CPU *cpu, GBE_Memory *memory);
void cpu_handle_interrupt(GBE_CPU *cpu, GBE_Memory *memory, u8 interrupt);

#endif // GBE_CPU_H
