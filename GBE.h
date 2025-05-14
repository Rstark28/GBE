/**
 * Game Boy Emulator (GBE) - Main Header File
 * Contains all core definitions, structures, and function declarations
 * for implementing a Game Boy emulator.
 */

#ifndef GBE_H
#define GBE_H

#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>

/****************************
 * Memory Map Constants
 ****************************/
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

#define ROM_BANK_SIZE 0x4000
#define VRAM_SIZE 0x2000
#define WRAM_SIZE 0x2000
#define OAM_SIZE 0xA0
#define IO_SIZE 0x80
#define HRAM_SIZE 0x7F

/****************************
 * CPU Register Constants
 ****************************/
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

/****************************
 * PPU Constants
 ****************************/
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define TILE_SIZE 8
#define TILES_PER_LINE 20
#define LINES_PER_FRAME 144

typedef enum {
        PPU_MODE_HBLANK = 0,
        PPU_MODE_VBLANK = 1,
        PPU_MODE_OAM = 2,
        PPU_MODE_VRAM = 3
} PPU_Mode;

/****************************
 * Interrupt Constants
 ****************************/
#define INT_VBLANK 0x40
#define INT_LCD 0x48
#define INT_TIMER 0x50
#define INT_SERIAL 0x58
#define INT_JOYPAD 0x60

/****************************
 * I/O Register Constants
 ****************************/
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

/****************************
 * CPU Structure
 *
 * uint8_t a: Accumulator
 * uint8_t f: Flags
 * uint8_t b: General purpose register B
 * uint8_t c: General purpose register C
 * uint8_t d: General purpose register D
 * uint8_t e: General purpose register E
 * uint8_t h: General purpose register H
 * uint8_t l: General purpose register L
 *
 * uint16_t pc: Program Counter
 * uint16_t sp: Stack Pointer
 *
 * bool halted: CPU halted state
 * bool ime: Interrupt Master Enable
 * int cycles: Number of cycles since last instruction
 ****************************/
typedef struct {
        // 8-bit registers
        uint8_t a; // Accumulator
        uint8_t f; // Flags
        uint8_t b;
        uint8_t c;
        uint8_t d;
        uint8_t e;
        uint8_t h;
        uint8_t l;

        // 16-bit registers
        uint16_t pc; // Program Counter
        uint16_t sp; // Stack Pointer

        // CPU state
        bool halted;
        bool ime; // Interrupt Master Enable
        int cycles;
} GBE_CPU;

/*****************************
 * PPU Structure
 *
 * uint8_t lcdc: LCD Control
 * uint8_t stat: LCD Status
 * uint8_t scy: Scroll Y
 * uint8_t scx: Scroll X
 * uint8_t ly: LCD Y Coordinate
 * uint8_t lyc: LY Compare
 * uint8_t bgp: BG Palette Data
 * uint8_t obp0: Object Palette 0
 * uint8_t obp1: Object Palette 1
 * uint8_t wy: Window Y Position
 * uint8_t wx: Window X Position
 *
 * PPU_Mode mode: Current PPU mode (HBLANK, VBLANK, OAM, VRAM)
 * int mode_clock: Clock cycles in current mode
 * uint8_t* framebuffer: Pointer to the framebuffer for rendering
 ****************************/
typedef struct {
        // Registers
        uint8_t lcdc; // LCD Control
        uint8_t stat; // LCD Status
        uint8_t scy;  // Scroll Y
        uint8_t scx;  // Scroll X
        uint8_t ly;   // LCD Y Coordinate
        uint8_t lyc;  // LY Compare
        uint8_t bgp;  // BG Palette Data
        uint8_t obp0; // Object Palette 0
        uint8_t obp1; // Object Palette 1
        uint8_t wy;   // Window Y Position
        uint8_t wx;   // Window X Position

        // Internal state
        PPU_Mode mode;
        int mode_clock;
        uint8_t *framebuffer;
} GBE_PPU;

/****************************
 * Memory Structure
 *
 * uint8_t* rom: Pointer to ROM banks
 * uint8_t* vram: Pointer to Video RAM
 * uint8_t* wram: Pointer to Work RAM
 * uint8_t* oam: Pointer to Object Attribute Memory
 * uint8_t* hram: Pointer to High RAM
 * uint8_t* io: Pointer to I/O registers
 *
 * uint8_t current_rom_bank: Current ROM bank number
 * uint8_t current_ram_bank: Current RAM bank number
 * bool ram_enabled: Flag indicating if RAM is enabled
 ****************************/
typedef struct {
        uint8_t *rom;  // ROM banks
        uint8_t *vram; // Video RAM
        uint8_t *wram; // Work RAM
        uint8_t *oam;  // Object Attribute Memory
        uint8_t *hram; // High RAM
        uint8_t *io;   // I/O registers

        // Memory banking
        uint8_t current_rom_bank;
        uint8_t current_ram_bank;
        bool ram_enabled;
} GBE_Memory;

/****************************
 * Cartridge Structure
 *
 * uint8_t* data: Pointer to cartridge data
 * uint32_t size: Size of the cartridge data
 * uint8_t type: Cartridge type (MBC1, MBC2, etc.)
 * uint8_t rom_banks: Number of ROM banks
 * uint8_t ram_banks: Number of RAM banks
 * bool has_battery: Flag indicating if the cartridge has a battery
 ****************************/
// Cartridge Structure
typedef struct {
        uint8_t *data;
        uint32_t size;
        uint8_t type;
        uint8_t rom_banks;
        uint8_t ram_banks;
        bool has_battery;
} GBE_Cartridge;

/****************************
 * Emulator Structure
 *
 * GBE_CPU* cpu: Pointer to the CPU structure
 * GBE_PPU* ppu: Pointer to the PPU structure
 * GBE_Memory* memory: Pointer to the Memory structure
 * GBE_Cartridge* cartridge: Pointer to the Cartridge structure
 * SDL_Window* window: Pointer to the SDL window
 * SDL_Renderer* renderer: Pointer to the SDL renderer
 * SDL_Texture* texture: Pointer to the SDL texture
 * bool running: Flag indicating if the emulator is running
 * uint32_t cycles: Number of cycles since last frame
 ****************************/
typedef struct {
        GBE_CPU *cpu;
        GBE_PPU *ppu;
        GBE_Memory *memory;
        GBE_Cartridge *cartridge;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        bool running;
        uint32_t cycles;
} GBE_Emulator;

// Core Emulator Functions
GBE_Emulator *GBE_Create(void);
void GBE_Destroy(GBE_Emulator *emu);
bool GBE_LoadROM(GBE_Emulator *emu, const char *rom_path);
void GBE_Step(GBE_Emulator *emu);

// CPU Functions
void GBE_CPU_Init(GBE_CPU *cpu);
void GBE_CPU_Step(GBE_CPU *cpu, GBE_Memory *memory);
void GBE_CPU_HandleInterrupt(GBE_CPU *cpu, GBE_Memory *memory, uint8_t interrupt);

// PPU Functions
void GBE_PPU_Init(GBE_PPU *ppu);
void GBE_PPU_Step(GBE_PPU *ppu, GBE_Memory *memory, int cycles);
void GBE_PPU_RenderScanline(GBE_PPU *ppu, GBE_Memory *memory);

// Memory Functions
bool GBE_Memory_Init(GBE_Memory *memory);
uint8_t GBE_Memory_Read(GBE_Memory *memory, uint16_t address);
void GBE_Memory_Write(GBE_Memory *memory, uint16_t address, uint8_t value);
void GBE_Memory_Cleanup(GBE_Memory *memory);

// Cartridge Functions
bool GBE_Cartridge_Load(GBE_Cartridge *cart, const char *path);
void GBE_Cartridge_Cleanup(GBE_Cartridge *cart);

// Utility Functions
uint8_t GBE_GetFlag(GBE_CPU *cpu, uint8_t flag);
void GBE_SetFlag(GBE_CPU *cpu, uint8_t flag, bool value);
uint16_t GBE_GetRegisterPair(GBE_CPU *cpu, uint8_t pair);
void GBE_SetRegisterPair(GBE_CPU *cpu, uint8_t pair, uint16_t value);

#endif // GBE_H
