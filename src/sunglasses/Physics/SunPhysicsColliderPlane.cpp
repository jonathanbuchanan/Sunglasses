// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Physics/SunPhysicsColliderPlane.h>
#include <sunglasses/Physics/SunPhysicsColliderAABB.h>
#include <sunglasses/Physics/SunPhysicsColliderSphere.h>
#include <sunglasses/Physics/SunPhysicsColliderMesh.h>
#include <sunglasses/Physics/GJKAlgorithm.h>

#include <glm/gtx/simd_vec4.hpp>

SunPhysicsColliderPlane::SunPhysicsColliderPlane() {
    setType(SunPhysicsColliderTypePlane);
}

SunPhysicsCollisionData SunPhysicsColliderPlane::collideWith(SunPhysicsCollider *other) {
    if (other->getType() == SunPhysicsColliderTypeSphere) {
        SunPhysicsColliderSphere *_other = static_cast<SunPhysicsColliderSphere *>(other);
        
        float distanceFromCenter = glm::dot(this->getNormal(), _other->getPosition()) - this->getDistance();
        
        float distanceFromSphere = distanceFromCenter - _other->getRadius();
        
        if (distanceFromSphere < 0)
            return SunPhysicsCollisionData(true, distanceFromSphere);
        else
            return SunPhysicsCollisionData(false, distanceFromSphere);
    } else if (other->getType() == SunPhysicsColliderTypeAABB) {
        SunPhysicsColliderAABB *_other = static_cast<SunPhysicsColliderAABB *> (other);

        glm::vec3 absoluteNormal = glm::vec3(glm::abs(this->getNormal().x), glm::abs(this->getNormal().y), glm::abs(this->getNormal().z));
        glm::vec3 extents = 0.5f * (_other->getSecondPoint() - _other->getFirstPoint());

        float c = glm::dot(_other->getPosition(), this->getNormal());
        float e = glm::dot(extents, absoluteNormal);
        if (this->getDistance() < c - e || this->getDistance() > c + e)
            return SunPhysicsCollisionData(false, c + e);
        else
            return SunPhysicsCollisionData(true, c + e);
    } else if (other->getType() == SunPhysicsColliderTypePlane) {
        SunPhysicsColliderPlane *_other = static_cast<SunPhysicsColliderPlane *>(other);
        
        if (_other->getNormal() != this->getNormal())
            return SunPhysicsCollisionData(true, 0);
        else
            return SunPhysicsCollisionData(false, 0);
    } else if (other->getType() == SunPhysicsColliderTypeMesh) {
        SunPhysicsColliderMesh *_other = static_cast<SunPhysicsColliderMesh *>(other);
        
        glm::vec3 farthestPointAlongNormal = getFarthestPointAlongAxis(_other, this->getNormal()) - this->getPosition();
        glm::vec3 farthestPointAlongOppNormal = getFarthestPointAlongAxis(_other, -this->getNormal()) - this->getPosition();
        
        float distance1 = glm::dot(farthestPointAlongNormal, this->getNormal());
        float distance2 = glm::dot(farthestPointAlongOppNormal, this->getNormal());
        
        if (distance1 > 0 && distance2 > 0)
            return SunPhysicsCollisionData(true, 0);
    }
    return SunPhysicsCollisionData(false, 0);
}
