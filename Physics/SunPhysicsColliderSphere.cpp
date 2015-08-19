#include "SunPhysicsColliderSphere.h"
#include "SunPhysicsColliderAABB.h"
#include "glm/gtx/string_cast.hpp"
#include <iostream>

SunPhysicsColliderSphere::SunPhysicsColliderSphere() {
    setType(SunPhysicsColliderTypeSphere);
}

SunPhysicsCollisionData SunPhysicsColliderSphere::collideWith(SunPhysicsCollider *other) {
    if (other->getType() == SunPhysicsColliderTypeSphere) {
        SunPhysicsColliderSphere *_other = static_cast<SunPhysicsColliderSphere *>(other);
        float centerDistance = glm::length(this->getPosition() - _other->getPosition());
        float radiusSum = this->getRadius() + _other->getRadius();
        
        if (radiusSum < centerDistance)
            return SunPhysicsCollisionData(false, 0);
        else
            return SunPhysicsCollisionData(true, centerDistance - radiusSum);
    } else if (other->getType() == SunPhysicsColliderTypeAABB) {
        SunPhysicsColliderAABB *_other = static_cast<SunPhysicsColliderAABB *>(other);
        
        glm::vec3 separatingAxis = this->getPosition() - _other->getPosition();
        float distance = glm::length(separatingAxis);
        
        separatingAxis = glm::normalize(separatingAxis);
        
        if (separatingAxis.x >= separatingAxis.y && separatingAxis.x >= separatingAxis.z)
            separatingAxis /= separatingAxis.x;
        else if (separatingAxis.y >= separatingAxis.x && separatingAxis.y >= separatingAxis.z)
            separatingAxis /= separatingAxis.y;
        else
            separatingAxis /= separatingAxis.z;
        
        separatingAxis.x *= _other->getWidth() / 2.0f;
        separatingAxis.y *= _other->getHeight() / 2.0f;
        separatingAxis.z *= _other->getDepth() / 2.0f;
        
        if (distance <= (this->getRadius() + glm::length(separatingAxis)))
            return SunPhysicsCollisionData(true, distance);
        else
            return SunPhysicsCollisionData(false, distance);
    }
    return SunPhysicsCollisionData(false, 0);
}