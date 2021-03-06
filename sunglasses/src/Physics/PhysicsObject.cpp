// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Physics/PhysicsObject.h>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace sunglasses {

PhysicsObject::PhysicsObject() {

}

void PhysicsObject::updatePositionForForcesAndDelta(std::vector<PhysicsForce> forces, float delta) {
    if (!stationary) {
        glm::vec3 netDirection = glm::vec3(0, 0, 0);
        for (size_t i = 0; i < forces.size(); i++)
            netDirection += forces[i].getDirectionWithForceForMass(mass);
        velocity += netDirection * delta;
        position += velocity * delta;
        for (size_t i = 0; i < colliders.size(); i++)
            colliders[i]->moveTo(position);
    }
}

} // namespace
