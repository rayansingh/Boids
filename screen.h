// screen.h - Defines related to SDL display
//

#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include "boid.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

void init_boids();
void kill_boids();
void update();
void update_boids(int t);
void refresh(SDL_Renderer* renderer);
void draw_boid(SDL_Renderer* renderer, Boid* boid);

#endif // SCREEN_H
