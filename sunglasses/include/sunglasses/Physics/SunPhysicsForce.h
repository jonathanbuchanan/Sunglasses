// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNPHYSICSFORCE_H
#define SUNPHYSICSFORCE_H

#include <glm/glm.hpp>

namespace sunglasses {

class SunPhysicsForce {
public:
    SunPhysicsForce();
    SunPhysicsForce(glm::vec3 _direction);
    
    glm::vec3 getDirectionWithForceForMass(float mass);
    
    inline glm::vec3 & getDirection() { return direction; }
    inline void setDirection(glm::vec3 _direction) { direction = _direction; }
    
    inline bool & getScalesWithMass() { return scalesWithMass; }
    inline void setScalesWithMass(bool _scalesWithMass) { scalesWithMass = _scalesWithMass; }
private:
    // The direction of the force (the force in newtons is the length)
    glm::vec3 direction;
    bool scalesWithMass = false;
};

} // namespace

#endif
