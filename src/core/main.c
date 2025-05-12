/**
 * Game Boy Emulator (GBE)
 * Main entry point and core emulator loop
 *
 * Development Roadmap:
 * 1. Bootstrapping & Setup ✓
 * 2. CPU Implementation
 * 3. Memory Bus
 * 4. Cartridge Support
 * 5. PPU Implementation
 * 6. Input Handling
 * 7. Timers
 * 8. Interrupts
 * 9. Audio (Optional)
 * 10. Serial Port (Optional)
 * 11. Save Support
 * 12. Performance & Polish
 */

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/core.h"

int main(int argc, char *argv[])
{
        if (argc < 2)
        {
                printf("Usage: %s <rom_file>\n", argv[0]);
                return 1;
        }

        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        {
                printf("SDL initialization failed: %s\n", SDL_GetError());
                return 1;
        }

        // Create window
        SDL_Window *window = SDL_CreateWindow(
            "GBE - Game Boy Emulator",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            160 * 4, // Scale up the 160x144 Game Boy resolution
            144 * 4,
            SDL_WINDOW_SHOWN);

        if (!window)
        {
                printf("Window creation failed: %s\n", SDL_GetError());
                SDL_Quit();
                return 1;
        }

        // TODO: Initialize emulator components
        // - CPU
        // - Memory
        // - PPU
        // - Input
        // - Timers
        // - Interrupts

        // Main emulator loop
        SDL_Event event;
        int running = 1;
        while (running)
        {
                while (SDL_PollEvent(&event))
                {
                        if (event.type == SDL_QUIT)
                        {
                                running = 0;
                        }
                        // TODO: Handle input events
                }

                // TODO: Emulate one frame
                // 1. Update CPU
                // 2. Update PPU
                // 3. Update timers
                // 4. Handle interrupts
        }

        // Cleanup
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
}
