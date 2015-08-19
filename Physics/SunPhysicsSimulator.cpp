#include "SunPhysicsSimulator.h"
#include <iostream>

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
    for (int i = 0; i < world.getObjects().size(); i++) {
        for (int j = i + 1; j < world.getObjects().size(); j++) {
            SunPhysicsCollisionData data = world.getObjectAtIndex(i)->collideWith(world.getObjectAtIndex(j));
            if (data.collided == true) {
                world.getObjectAtIndex(i)->setVelocity(glm::vec3(0.0, 5.0, 0.0));
            }
        }
    }
}

void SunPhysicsSimulator::respondToCollisions(float delta) {
    
}