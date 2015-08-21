#include "SunPhysicsColliderAABB.h"
#include "SunPhysicsColliderSphere.h"
#include "SunPhysicsColliderPlane.h"
#include "glm/gtx/simd_vec4.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/simd_quat.hpp"
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
    } else if (other->getType() == SunPhysicsColliderTypeSphere) {
        SunPhysicsColliderSphere *_other = static_cast<SunPhysicsColliderSphere *>(other);
        
        glm::vec3 separatingAxis = _other->getPosition() - this->getPosition();
        float distance = glm::length(separatingAxis);

        separatingAxis = glm::normalize(separatingAxis);

        if (separatingAxis.x >= separatingAxis.y && separatingAxis.x >= separatingAxis.z)
            separatingAxis /= separatingAxis.x;
        else if (separatingAxis.y >= separatingAxis.x && separatingAxis.y >= separatingAxis.z)
            separatingAxis /= separatingAxis.y;
        else
            separatingAxis /= separatingAxis.z;

        separatingAxis.x *= this->getWidth() / 2.0f;
        separatingAxis.y *= this->getHeight() / 2.0f;
        separatingAxis.z *= this->getDepth() / 2.0f;

        if (distance <= (_other->getRadius() + glm::length(separatingAxis)))
            return SunPhysicsCollisionData(true, distance);
        else
            return SunPhysicsCollisionData(false, distance);
    } else if (other->getType() == SunPhysicsColliderTypePlane) {
        SunPhysicsColliderPlane *_other = static_cast<SunPhysicsColliderPlane *>(other);
        
        glm::vec3 absoluteNormal = glm::vec3(glm::abs(_other->getNormal().x), glm::abs(_other->getNormal().y), glm::abs(_other->getNormal().z));
        glm::vec3 extents = 0.5f * (this->getSecondPoint() - this->getFirstPoint());
        
        float c = glm::dot(this->getPosition(), _other->getNormal());
        float e = glm::dot(extents, absoluteNormal);
        if (_other->getDistance() < c - e || _other->getDistance() > c + e)
            return SunPhysicsCollisionData(false, c + e);
        else
            return SunPhysicsCollisionData(true, c + e);
    }
    return SunPhysicsCollisionData(false, 0);
}