#include "GBE.h"

GBE_Emulator *GBE_Create(void)
{
        GBE_Emulator *emu = (GBE_Emulator *)malloc(sizeof(GBE_Emulator));
        if (!emu) {
                fprintf(stderr, "Failed to allocate memory for emulator\n");
                return NULL;
        }

        emu->cpu = (GBE_CPU *)malloc(sizeof(GBE_CPU));
        emu->ppu = (GBE_PPU *)malloc(sizeof(GBE_PPU));
        emu->memory = (GBE_Memory *)malloc(sizeof(GBE_Memory));
        emu->cartridge = (GBE_Cartridge *)malloc(sizeof(GBE_Cartridge));

        if (!emu->cpu || !emu->ppu || !emu->memory || !emu->cartridge) {
                fprintf(stderr, "Failed to allocate memory for emulator components\n");
                GBE_Destroy(emu);
                return NULL;
        }

        emu->running = true;
        emu->cycles = 0;

        return emu;
}

void GBE_Destroy(GBE_Emulator *emu)
{
        if (emu) {
                free(emu->cpu);
                free(emu->ppu);
                free(emu->memory);
                free(emu->cartridge);
                free(emu);
        }
}
