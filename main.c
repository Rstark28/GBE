#include <SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/********** main **********
 * Main function for the CHIP-8 emulator.
 *
 * Parameters:
 *      argc:      Argument count
 *      argv:      Argument vector
 *
 * Returns:
 *      int:       Exit status
 *
 * Notes:
 *      Initializes SDL, creates a window, and enters the main loop.
 ************************/
int main(int argc, char **argv)
{
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
                fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
                return 1;
        }

        // Create SDL window
        SDL_Window *window =
            SDL_CreateWindow("GBE Emulator", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, 160 * 3, 144 * 3, SDL_WINDOW_SHOWN);
        if (!window) {
                fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
                SDL_Quit();
                return 1;
        }

        // Create SDL renderer
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
                fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 1;
        }

        // Load ROM file
        if (argc < 2) {
                fprintf(stderr, "Usage: %s <romfile>\n", argv[0]);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 1;
        }
        FILE *rom = fopen(argv[1], "rb");
        if (!rom) {
                fprintf(stderr, "Failed to open ROM file: %s\n", argv[1]);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 1;
        }
        fseek(rom, 0, SEEK_END);
        uint32_t rom_size = ftell(rom);
        fseek(rom, 0, SEEK_SET);
        unsigned char *rom_data = malloc(rom_size);
        if (!rom_data) {
                fprintf(stderr, "Failed to allocate memory for ROM\n");
                fclose(rom);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 1;
        }
        uint32_t read_size = fread(rom_data, 1, rom_size, rom);
        if (read_size != rom_size) {
                fprintf(stderr, "Failed to read ROM file\n");
                free(rom_data);
                fclose(rom);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 1;
        }
        fclose(rom);

        // Emulator state initialization would go here
        // (CPU, memory, GPU, etc.)

        // Main emulation loop
        uint8_t running = 1;
        SDL_Event event;
        while (running) {
                // Handle SDL events (input, quit, etc.)
                while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                                running = 0;
                        }
                        // Handle input events here
                }

                // Emulate CPU cycles
                // cpu_step();

                // Update graphics
                // gpu_step();

                // Render frame (placeholder)
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                // draw_framebuffer(renderer);
                SDL_RenderPresent(renderer);

                // Timing control (placeholder)
                SDL_Delay(16); // ~60 FPS
        }

        // Cleanup
        free(rom_data);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
}