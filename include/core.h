/**
 * Core emulator header file
 * Contains common definitions and structures used throughout the emulator
 */

#ifndef GBE_CORE_H
#define GBE_CORE_H

#include <stdint.h>
#include <stdbool.h>

// Common type definitions
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

// Game Boy screen dimensions
#define GB_SCREEN_WIDTH 160
#define GB_SCREEN_HEIGHT 144

// Memory map constants
#define ROM_BANK_0_START 0x0000
#define ROM_BANK_0_END 0x3FFF
#define VRAM_START 0x8000
#define VRAM_END 0x9FFF
#define OAM_START 0xFE00
#define OAM_END 0xFE9F
#define IO_START 0xFF00
#define IO_END 0xFF7F

// Error codes
typedef enum
{
        GBE_OK = 0,
        GBE_ERROR_ROM_LOAD,
        GBE_ERROR_INIT,
        GBE_ERROR_MEMORY,
        GBE_ERROR_CPU,
        GBE_ERROR_PPU
} GBE_Error;

// Forward declarations
typedef struct GBE_CPU GBE_CPU;
typedef struct GBE_PPU GBE_PPU;
typedef struct GBE_Memory GBE_Memory;
typedef struct GBE_Cartridge GBE_Cartridge;

// Main emulator structure
typedef struct
{
        GBE_CPU *cpu;
        GBE_PPU *ppu;
        GBE_Memory *memory;
        GBE_Cartridge *cartridge;
        bool running;
        u32 cycles;
} GBE_Emulator;

// Function declarations
GBE_Error gbe_init(GBE_Emulator *emu, const char *rom_path);
void gbe_run(GBE_Emulator *emu);
void gbe_cleanup(GBE_Emulator *emu);

#endif // GBE_CORE_H
