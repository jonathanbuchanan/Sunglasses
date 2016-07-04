// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Physics/SunPhysicsForce.h>
#include <iostream>

SunPhysicsForce::SunPhysicsForce() {

}

SunPhysicsForce::SunPhysicsForce(glm::vec3 _direction) {
    setDirection(_direction);
}

glm::vec3 SunPhysicsForce::getDirectionWithForceForMass(float mass) {
    if (mass == 0)
        return glm::vec3(0, 0, 0);
    if (!scalesWithMass)
        return direction * (1 / mass);
    else
        return direction;
}
