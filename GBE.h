/**
 * Game Boy Emulator (GBE) - Main Header File
 * Contains all core definitions, structures, and function declarations
 * for implementing a Game Boy emulator.
 */

#ifndef GBE_H
#define GBE_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

/* ===== Type Definitions ===== */
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

/* ===== Memory Constants ===== */
// Memory Map
#define ROM_BANK_0_START 0x0000
#define ROM_BANK_0_END 0x3FFF
#define ROM_BANK_N_START 0x4000
#define ROM_BANK_N_END 0x7FFF
#define VRAM_START 0x8000
#define VRAM_END 0x9FFF
#define EXTERNAL_RAM_START 0xA000
#define EXTERNAL_RAM_END 0xBFFF
#define WRAM_START 0xC000
#define WRAM_END 0xDFFF
#define ECHO_RAM_START 0xE000
#define ECHO_RAM_END 0xFDFF
#define OAM_START 0xFE00
#define OAM_END 0xFE9F
#define UNUSED_START 0xFEA0
#define UNUSED_END 0xFEFF
#define IO_START 0xFF00
#define IO_END 0xFF7F
#define HRAM_START 0xFF80
#define HRAM_END 0xFFFE
#define IE_REGISTER 0xFFFF

// Memory Sizes
#define ROM_BANK_SIZE 0x4000
#define VRAM_SIZE 0x2000
#define WRAM_SIZE 0x2000
#define OAM_SIZE 0xA0
#define IO_SIZE 0x80
#define HRAM_SIZE 0x7F

/* ===== CPU Registers ===== */
// Register pairs
#define REG_AF 0
#define REG_BC 1
#define REG_DE 2
#define REG_HL 3
#define REG_SP 4
#define REG_PC 5

// Flags
#define FLAG_Z 7 // Zero flag
#define FLAG_N 6 // Subtract flag
#define FLAG_H 5 // Half carry flag
#define FLAG_C 4 // Carry flag

/* ===== PPU Constants ===== */
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define TILE_SIZE 8
#define TILES_PER_LINE 20
#define LINES_PER_FRAME 144

// PPU Modes
typedef enum {
        PPU_MODE_HBLANK = 0,
        PPU_MODE_VBLANK = 1,
        PPU_MODE_OAM = 2,
        PPU_MODE_VRAM = 3
} PPU_Mode;

/* ===== Interrupt Vectors ===== */
#define INT_VBLANK 0x40
#define INT_LCD 0x48
#define INT_TIMER 0x50
#define INT_SERIAL 0x58
#define INT_JOYPAD 0x60

/* ===== I/O Register Addresses ===== */
#define REG_JOYP 0xFF00 // Joypad
#define REG_SB 0xFF01   // Serial transfer data
#define REG_SC 0xFF02   // Serial transfer control
#define REG_DIV 0xFF04  // Divider register
#define REG_TIMA 0xFF05 // Timer counter
#define REG_TMA 0xFF06  // Timer modulo
#define REG_TAC 0xFF07  // Timer control
#define REG_IF 0xFF0F   // Interrupt flag
#define REG_LCDC 0xFF40 // LCD control
#define REG_STAT 0xFF41 // LCD status
#define REG_SCY 0xFF42  // Scroll Y
#define REG_SCX 0xFF43  // Scroll X
#define REG_LY 0xFF44   // LCD Y coordinate
#define REG_LYC 0xFF45  // LCD Y compare
#define REG_DMA 0xFF46  // DMA transfer
#define REG_BGP 0xFF47  // BG palette data
#define REG_OBP0 0xFF48 // Object palette 0
#define REG_OBP1 0xFF49 // Object palette 1
#define REG_WY 0xFF4A   // Window Y position
#define REG_WX 0xFF4B   // Window X position
#define REG_IE 0xFFFF   // Interrupt enable

/* ===== Core Structures ===== */

// CPU Structure
typedef struct {
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

        // CPU state
        bool halted;
        bool ime; // Interrupt Master Enable
        int cycles;
} GBE_CPU;

// PPU Structure
typedef struct {
        // Registers
        u8 lcdc; // LCD Control
        u8 stat; // LCD Status
        u8 scy;  // Scroll Y
        u8 scx;  // Scroll X
        u8 ly;   // LCD Y Coordinate
        u8 lyc;  // LY Compare
        u8 bgp;  // BG Palette Data
        u8 obp0; // Object Palette 0
        u8 obp1; // Object Palette 1
        u8 wy;   // Window Y Position
        u8 wx;   // Window X Position

        // Internal state
        PPU_Mode mode;
        int mode_clock;
        u8 *framebuffer;
} GBE_PPU;

// Memory Structure
typedef struct {
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

// Cartridge Structure
typedef struct {
        u8 *data;
        u32 size;
        u8 type;
        u8 rom_banks;
        u8 ram_banks;
        bool has_battery;
} GBE_Cartridge;

// Main Emulator Structure
typedef struct {
        GBE_CPU *cpu;
        GBE_PPU *ppu;
        GBE_Memory *memory;
        GBE_Cartridge *cartridge;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        bool running;
        u32 cycles;
} GBE_Emulator;

/* ===== Function Declarations ===== */

// Core Emulator Functions
GBE_Emulator *GBE_Create(void);
void GBE_Destroy(GBE_Emulator *emu);
bool GBE_LoadROM(GBE_Emulator *emu, const char *rom_path);
void GBE_Run(GBE_Emulator *emu);
void GBE_Step(GBE_Emulator *emu);

// CPU Functions
void GBE_CPU_Init(GBE_CPU *cpu);
void GBE_CPU_Step(GBE_CPU *cpu, GBE_Memory *memory);
void GBE_CPU_HandleInterrupt(GBE_CPU *cpu, GBE_Memory *memory, u8 interrupt);

// PPU Functions
void GBE_PPU_Init(GBE_PPU *ppu);
void GBE_PPU_Step(GBE_PPU *ppu, GBE_Memory *memory, int cycles);
void GBE_PPU_RenderScanline(GBE_PPU *ppu, GBE_Memory *memory);

// Memory Functions
bool GBE_Memory_Init(GBE_Memory *memory);
u8 GBE_Memory_Read(GBE_Memory *memory, u16 address);
void GBE_Memory_Write(GBE_Memory *memory, u16 address, u8 value);
void GBE_Memory_Cleanup(GBE_Memory *memory);

// Cartridge Functions
bool GBE_Cartridge_Load(GBE_Cartridge *cart, const char *path);
void GBE_Cartridge_Cleanup(GBE_Cartridge *cart);

// Utility Functions
u8 GBE_GetFlag(GBE_CPU *cpu, u8 flag);
void GBE_SetFlag(GBE_CPU *cpu, u8 flag, bool value);
u16 GBE_GetRegisterPair(GBE_CPU *cpu, u8 pair);
void GBE_SetRegisterPair(GBE_CPU *cpu, u8 pair, u16 value);

#endif // GBE_H
