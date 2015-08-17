#include "SunPhysicsSimulator.h"

void SunPhysicsSimulator::cycle(float delta) {
    integrate(delta);
    detectCollisions(delta);
    respondToCollisions(delta);
}

void SunPhysicsSimulator::integrate(float delta) {
    vector<SunPhysicsForce> forces;
    forces.push_back(world.getGravity());
    for (int i = 0; i < world.getObjects().size(); i++) {
        world.getObjectAtIndex(i)->updatePositionForForcesAndDelta(forces, delta);
    }
}

void SunPhysicsSimulator::detectCollisions(float delta) {
    
}

void SunPhysicsSimulator::respondToCollisions(float delta) {
    
}