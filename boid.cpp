// boid.cpp
//

#include "boid.h"
#include <cmath>
#include "screen.h"

Boid::Boid() {
    x_pos = (float)(rand()%SCREEN_WIDTH);
    y_pos = (float)(rand()%SCREEN_HEIGHT);

    x_vel = ((float)(rand()%10)-5.0f);
    y_vel = ((float)(rand()%10)-5.0f);

    a = rand()%255;
}

void Boid::seek() {

    float avg_x_pos = 0.0f;
    float avg_y_pos = 0.0f;
    int num_close = 0;

    for (int i = 0; i < NUM_BOIDS; i++) {
        Boid* other = boids[i];

        float distance_from = sqrt(pow(x_pos-other->x_pos,2) + pow(y_pos-other->y_pos,2)); 

        if (distance_from <= static_cast<float>(MAX_SEEK_DISTANCE)) {
            avg_x_pos += other->x_pos;
            avg_y_pos += other->y_pos;

            num_close++;
        }
    }  

    if (num_close) {
        avg_x_pos /= static_cast<float>(num_close);
        avg_y_pos /= static_cast<float>(num_close);

        x_vel += SEEK_DAMPING * (avg_x_pos-x_pos);
        y_vel += SEEK_DAMPING * (avg_y_pos-y_pos);
    }

}

void Boid::align() {

    float avg_x_vel = 0.0f;
    float avg_y_vel = 0.0f;
    int num_close = 0;

    for (int i = 0; i < NUM_BOIDS; i++) {
        Boid* other = boids[i];

        float distance_from = sqrt(pow(x_pos-other->x_pos,2) + pow(y_pos-other->y_pos,2)); 

        if (distance_from <= static_cast<float>(MAX_ALIGN_DISTANCE)) {
            avg_x_vel += other->x_pos;
            avg_y_vel += other->y_pos;

            num_close++;
        }
    }  

    if (num_close) {
        avg_x_vel /= static_cast<float>(num_close);
        avg_y_vel /= static_cast<float>(num_close);

        x_vel += ALIGN_DAMPING * (avg_x_vel-x_pos);
        y_vel += ALIGN_DAMPING * (avg_y_vel-y_pos);
    }

}

void Boid::avoid() {

    float delta_x = 0.0f;
    float delta_y = 0.0f;

    for (int i = 0; i < NUM_BOIDS; i++) {
        Boid* other = boids[i];

        float distance_from = sqrt(pow(x_pos-other->x_pos,2) + pow(y_pos-other->y_pos,2)); 

        if (distance_from <= static_cast<float>(MAX_AVOID_DISTANCE)) {
            delta_x += x_pos - other->x_pos;
            delta_y += y_pos - other->y_pos;
        }
    }  

    x_vel += AVOID_DAMPING * delta_x;
    y_vel += AVOID_DAMPING * delta_y;
}

void Boid::update_position() {

    x_vel += 2.0f * ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) - 0.5f);
    y_vel += 2.0f * ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) - 0.5f);

    x_vel = std::fmin(x_vel,MAX_SPEED);
    y_vel = std::fmin(y_vel,MAX_SPEED);

    x_pos += x_vel;
    y_pos += y_vel;

    #ifndef BOUNCY 
        if (x_pos < 0.0f) {
            x_pos = static_cast<float>(SCREEN_WIDTH)-1.0f;
        } else if (x_pos > static_cast<float>(SCREEN_WIDTH)) {
            x_pos = 0.0f;
        }

        if (y_pos < 0.0f) {
            y_pos = static_cast<float>(SCREEN_HEIGHT)-1.0f;
        } else if (y_pos > static_cast<float>(SCREEN_HEIGHT)) {
            y_pos = 0.0f;
        }
    #else
        if (x_pos < 0.0f) {
            x_pos = 0.0f;
            x_vel = -x_vel*BOUNCE_DAMPING;
        } else if (x_pos > static_cast<float>(SCREEN_WIDTH)) {
            x_pos = static_cast<float>(SCREEN_WIDTH);
            x_vel = -x_vel*BOUNCE_DAMPING;
        }

        if (y_pos < 0.0f) {
            y_pos = 0.0f;
            y_vel = -y_vel*BOUNCE_DAMPING;
        } else if (y_pos > static_cast<float>(SCREEN_HEIGHT)) {
            y_pos = static_cast<float>(SCREEN_HEIGHT);
            y_vel = -y_vel*BOUNCE_DAMPING;
        }
    #endif

}
