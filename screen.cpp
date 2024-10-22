// screen.c - Functions defined in screen.h
//

#include "screen.h"
#include "SDL2/SDL_render.h"
#include "boid.h"
#include <iostream>

Boid* boids[NUM_BOIDS];

void init_boids() {
    for (int i = 0; i < NUM_BOIDS; i++) {
        boids[i] = new Boid();
    }
}

void kill_boids() {
    for (int i = 0; i < NUM_BOIDS; i++) {
        delete boids[i];
    }
}

void refresh(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < NUM_BOIDS; i++) {
        draw_boid(renderer,boids[i]);
    }

    SDL_RenderPresent(renderer);
}

void update_boids(int t) {

    if (t%2 == 0) {
        for (int i = 0; i < NUM_BOIDS; i++) {
            boids[i]->seek();
            boids[i]->avoid();
            boids[i]->align();
        }
    }

    for (int i = 0; i < NUM_BOIDS; i++) {
        boids[i]->update_position();
    }

}

void draw_boid(SDL_Renderer* renderer, Boid* boid) {
    for (int i = 0; i < BOID_WIDTH; i++) {
        for (int j = 0; j < BOID_WIDTH; j++) {

            float px = boid->x_pos+static_cast<float>(i-(int)BOID_RADIUS);
            float py = boid->y_pos+static_cast<float>(j-(int)BOID_RADIUS);


            float magnitude = sqrtf(pow(boid->x_vel,2)+pow(boid->y_vel,2));

            magnitude /= static_cast<float>(MAX_SPEED);

            SDL_SetRenderDrawColor(renderer, magnitude*255, 255-magnitude*255, 100, boid->a);
            

            if (sqrt(pow(px-boid->x_pos,2)+pow(py-boid->y_pos,2)) < static_cast<float>(BOID_RADIUS)) SDL_RenderDrawPoint(renderer, px, py);

            SDL_RenderDrawLine(renderer,boid->x_pos,boid->y_pos,boid->x_pos+2.0f*boid->x_vel,boid->y_pos+2.0f*boid->y_vel);
 
        }
    }
}