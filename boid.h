// boid.h
//

#ifndef BOID_H
#define BOID_H

#define BOUNCY

#define BOID_WIDTH 5
#define BOID_RADIUS (BOID_WIDTH/2)

#define NUM_BOIDS 200

#define MAX_SEEK_DISTANCE 75
#define MAX_AVOID_DISTANCE 20
#define MAX_ALIGN_DISTANCE 75
#define MAX_SPEED 10.0f

#define SEEK_DAMPING 0.03f
#define AVOID_DAMPING 0.12f
#define ALIGN_DAMPING 0.05f
#define BOUNCE_DAMPING 0.5f

#include <cstdint>

class Boid {
public:
    float x_pos;
    float y_pos;
    float x_vel;
    float y_vel;

    uint8_t a;

    Boid();
    void update_position();

    void seek(); // Cohesion
    void avoid(); // Separation
    void align(); // Alignment
};

extern Boid* boids[NUM_BOIDS];

#endif // BOID_H
