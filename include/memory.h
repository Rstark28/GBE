/**
 * Memory management header
 *
 * Implementation Tasks:
 * 1. Memory map implementation
 * 2. Read/write functions
 * 3. RAM, ROM, I/O registers
 * 4. Zero-page handling
 * 5. Interrupt vector table
 */

#ifndef GBE_MEMORY_H
#define GBE_MEMORY_H

#include "core.h"

// Memory structure
typedef struct
{
        u8 *rom;  // ROM banks
        u8 *vram; // Video RAM
        u8 *wram; // Work RAM
        u8 *oam;  // Object Attribute Memory
        u8 *hram; // High RAM
        u8 *io;   // I/O registers

        // Memory banking
        u8 current_rom_bank;
        u8 current_ram_bank;
        bool ram_enabled;
} GBE_Memory;

// Function declarations
GBE_Error memory_init(GBE_Memory *memory);
u8 memory_read(GBE_Memory *memory, u16 address);
void memory_write(GBE_Memory *memory, u16 address, u8 value);
void memory_cleanup(GBE_Memory *memory);

#endif // GBE_MEMORY_H
