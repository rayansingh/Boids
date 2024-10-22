// screen.c - Functions defined in screen.h
//

#include "screen.h"
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    for (int i = 0; i < NUM_BOIDS; i++) {
        draw_boid(renderer,boids[i]);
    }

    SDL_RenderPresent(renderer);
}

void update_boids() {
    // float total_x_vel = 0.0f;
    // float total_y_vel = 0.0f;

    for (int i = 0; i < NUM_BOIDS; i++) {
        for (int j = i+1; j < NUM_BOIDS; j++) {
            boids[i]->touch(boids[j]);
        }
    }
    for (int i = 0; i < NUM_BOIDS; i++) {
        boids[i]->update_position();
        // total_x_vel += boids[i]->x_vel;
        // total_y_vel += boids[i]->y_vel;
    }

    // std::cout<< sqrt(pow(total_x_vel,2) + pow(total_y_vel,2)) << std::endl;
}

void draw_boid(SDL_Renderer* renderer, Boid* boid) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, rand()%255);
    SDL_RenderDrawPoint(renderer, boid->x_pos,boid->y_pos);
}