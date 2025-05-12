/**
 * PPU (Graphics) implementation header
 *
 * Implementation Tasks:
 * 1. VRAM and OAM management
 * 2. Tile fetching
 * 3. Sprite handling
 * 4. Scanline rendering
 * 5. VBlank/HBlank timing
 * 6. LCD control registers
 */

#ifndef GBE_PPU_H
#define GBE_PPU_H

#include "core.h"

// PPU modes
typedef enum
{
        PPU_MODE_HBLANK = 0,
        PPU_MODE_VBLANK = 1,
        PPU_MODE_OAM = 2,
        PPU_MODE_VRAM = 3
} PPU_Mode;

// PPU structure
typedef struct
{
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

// Function declarations
void ppu_init(GBE_PPU *ppu);
void ppu_step(GBE_PPU *ppu, GBE_Memory *memory, int cycles);
void ppu_render_scanline(GBE_PPU *ppu, GBE_Memory *memory);
void ppu_cleanup(GBE_PPU *ppu);

#endif // GBE_PPU_H
