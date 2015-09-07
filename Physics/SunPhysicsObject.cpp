#include "SunPhysicsObject.h"
#include "glm/gtx/string_cast.hpp"
#include <iostream>

SunPhysicsObject::SunPhysicsObject() {
    
}

void SunPhysicsObject::updatePositionForForcesAndDelta(vector<SunPhysicsForce> forces, float delta) {
    if (!stationary) {
        glm::vec3 netDirection = glm::vec3(0, 0, 0);
        for (int i = 0; i < forces.size(); i++)
            netDirection += forces[i].getDirectionWithForceForMass(mass);
        velocity += netDirection * delta;
        position += velocity * delta;
        for (int i = 0; i < colliders.size(); i++)
            colliders[i]->moveTo(position);
    }
}