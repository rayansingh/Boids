// boid.cpp
//

#include "boid.h"
#include "screen.h"
#include <cmath>

Boid::Boid() {
    x_pos = (float)(rand()%SCREEN_WIDTH);
    y_pos = (float)(rand()%SCREEN_HEIGHT);

    x_vel = ((float)(rand()%10)-5.0f)/1.0f;
    y_vel = ((float)(rand()%10)-5.0f)/1.0f;
    // x_vel = 1.0f;
    // y_vel = 1.0f;

    x_acc = 0.0f;
    y_acc = 0.0f;
}

void Boid::touch(Boid* other) {

   float distance_from = (float)sqrt(pow((int)(x_pos-other->x_pos),2) + pow((int)(y_pos-other->y_pos),2)); 

   if (distance_from > MAX_INFLUENCE_DISTANCE) return;


   float influence_function = 1.0f - (distance_from/static_cast<float>(MAX_INFLUENCE_DISTANCE));

   // Cohesion Rule
   float influence = influence_function;

   float x_pos_diff = (other->x_pos - x_pos)/(MAX_INFLUENCE_DISTANCE);
   float y_pos_diff = (other->y_pos - y_pos)/(MAX_INFLUENCE_DISTANCE);

   x_vel += x_pos_diff*influence;
   y_vel += y_pos_diff*influence;

   other->x_vel -= x_pos_diff*influence;
   other->y_vel -= y_pos_diff*influence;

}

void Boid::update_position() {

    // x_acc += ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) - 0.5f);
    // y_acc += ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) - 0.5f);

    x_vel += x_acc;
    y_vel += y_acc;
    x_pos += x_vel;
    y_pos += y_vel;

    if (x_pos < 0.0f) {
        x_pos = 0.0f;
        x_vel = -x_vel;
    } else if (x_pos > static_cast<float>(SCREEN_WIDTH)) {
        x_pos = static_cast<float>(SCREEN_WIDTH);
        x_vel = -x_vel;
    }

    if (y_pos < 0.0f) {
        y_pos = 0.0f;
        y_vel = -y_vel;
    } else if (y_pos > static_cast<float>(SCREEN_HEIGHT)) {
        y_pos = static_cast<float>(SCREEN_HEIGHT);
        y_vel = -y_vel;
    }

    x_acc = 0.0f;
    y_acc = 0.0f;
}
