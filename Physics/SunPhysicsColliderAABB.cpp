#include "SunPhysicsColliderAABB.h"
#include "glm/gtx/simd_vec4.hpp"
#include "glm/gtx/string_cast.hpp"
#include <string>
#include <iostream>

SunPhysicsColliderAABB::SunPhysicsColliderAABB() {
    setType(SunPhysicsColliderTypeAABB);
}

SunPhysicsCollisionData SunPhysicsColliderAABB::collideWith(SunPhysicsCollider *other) {
    if (other->getType() == SunPhysicsColliderTypeAABB) {
        SunPhysicsColliderAABB *_other = static_cast<SunPhysicsColliderAABB *>(other);
        glm::vec3 first = this->getFirstPoint() - _other->getSecondPoint();
        glm::vec3 second = _other->getFirstPoint() - this->getSecondPoint();
        
//        std::cout << "First: " + glm::to_string(firstPoint) + "\n" << std::flush;
//        std::cout << "Second: " + glm::to_string(secondPoint) + "\n" << std::flush;
//        
//        std::cout << "First: " + glm::to_string(_other->getFirstPoint()) + "\n" << std::flush;
//        std::cout << "Second: " + glm::to_string(_other->getSecondPoint()) + "\n" << std::flush;
        
        if (glm::length(first) < glm::length(second)) {
            if (_other->getSecondPoint().x < this->getFirstPoint().x || _other->getSecondPoint().y < this->getFirstPoint().y || _other->getSecondPoint().z < this->getFirstPoint().z)
                return SunPhysicsCollisionData(false, 0);
            else
                return SunPhysicsCollisionData(true, glm::length(first));
        } else {
            if (this->getSecondPoint().x < _other->getFirstPoint().x || this->getSecondPoint().y < _other->getFirstPoint().y || this->getSecondPoint().z < _other->getSecondPoint().z)
                return SunPhysicsCollisionData(false, 0);
            else
                return SunPhysicsCollisionData(true, glm::length(second));
        }
    }
    return SunPhysicsCollisionData(false, 0);
}