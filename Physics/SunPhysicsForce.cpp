#include "SunPhysicsForce.h"
#include <iostream>
using namespace std;

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