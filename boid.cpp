// boid.cpp
//

#include "boid.h"
#include "screen.h"
#include <cmath>

Boid::Boid() {
    x_pos = (float)(rand()%SCREEN_WIDTH);
    y_pos = (float)(rand()%SCREEN_HEIGHT);

    x_vel = ((float)(rand()%10)-5.0f)/10.0f;
    y_vel = ((float)(rand()%10)-5.0f)/10.0f;
    // x_vel = 1.0f;
    // y_vel = 1.0f;

    x_acc = 0.0f;
    y_acc = 0.0f;
}

void Boid::touch(Boid* other) {

   float distance_from = (float)sqrt(pow((int)(x_pos-other->x_pos),2) + pow((int)(y_pos-other->y_pos),2)); 

   if (distance_from > MAX_INFLUENCE_DISTANCE) return;

   // Linear influence
//    float influence = 0.5*((distance_from)/(1.0f*MAX_INFLUENCE_DISTANCE));

   // Quadratic influence (y = x^3)
   float influence = 1.0;

   float x_vel_diff = (other->x_vel - x_vel)/(MAX_INFLUENCE_DISTANCE);
   float y_vel_diff = (other->y_vel - y_vel)/(MAX_INFLUENCE_DISTANCE);

   x_acc += x_vel_diff*influence;
   y_acc += y_vel_diff*influence;

   other->x_acc -= x_vel_diff*influence;
   other->y_acc -= y_vel_diff*influence;

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
