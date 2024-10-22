// boid.h
//

#ifndef BOID_H
#define BOID_H

#define NUM_BOIDS 1000
#define MAX_INFLUENCE_DISTANCE 50

class Boid {
public:
    float x_pos;
    float y_pos;
    float x_vel;
    float y_vel;
    float x_acc;
    float y_acc;

    Boid();
    void update_position();

    void touch(Boid *other);
};

extern Boid* boids[NUM_BOIDS];

#endif // BOID_H
