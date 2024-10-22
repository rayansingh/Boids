#include "screen.h"
#include <time.h>
#include <iostream>
#include <unistd.h>

int main() {

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH,SCREEN_HEIGHT,0,&window,&renderer);

    SDL_RenderClear(renderer);

    SDL_PumpEvents();

    init_boids();
    
    uint8_t running = 1;

    while(running) {
        SDL_Event event;

        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                break;
            }
        }

        usleep(10000);
        update_boids();
        refresh(renderer);
    }

    kill_boids();

    // Clean up resources
    SDL_DestroyWindow(window);
    SDL_Quit();
}
