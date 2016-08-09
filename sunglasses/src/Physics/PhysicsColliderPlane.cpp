// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Physics/PhysicsColliderPlane.h>
#include <sunglasses/Physics/PhysicsColliderAABB.h>
#include <sunglasses/Physics/PhysicsColliderSphere.h>
#include <sunglasses/Physics/PhysicsColliderMesh.h>
#include <sunglasses/Physics/GJKAlgorithm.h>

#include <glm/gtx/simd_vec4.hpp>

namespace sunglasses {

PhysicsColliderPlane::PhysicsColliderPlane() {
    setType(PhysicsColliderTypePlane);
}

PhysicsCollisionData PhysicsColliderPlane::collideWith(PhysicsCollider *other) {
    if (other->getType() == PhysicsColliderTypeSphere) {
        PhysicsColliderSphere *_other = static_cast<PhysicsColliderSphere *>(other);
        
        float distanceFromCenter = glm::dot(this->getNormal(), _other->getPosition()) - this->getDistance();
        
        float distanceFromSphere = distanceFromCenter - _other->getRadius();
        
        if (distanceFromSphere < 0)
            return PhysicsCollisionData(true, distanceFromSphere);
        else
            return PhysicsCollisionData(false, distanceFromSphere);
    } else if (other->getType() == PhysicsColliderTypeAABB) {
        PhysicsColliderAABB *_other = static_cast<PhysicsColliderAABB *> (other);

        glm::vec3 absoluteNormal = glm::vec3(glm::abs(this->getNormal().x), glm::abs(this->getNormal().y), glm::abs(this->getNormal().z));
        glm::vec3 extents = 0.5f * (_other->getSecondPoint() - _other->getFirstPoint());

        float c = glm::dot(_other->getPosition(), this->getNormal());
        float e = glm::dot(extents, absoluteNormal);
        if (this->getDistance() < c - e || this->getDistance() > c + e)
            return PhysicsCollisionData(false, c + e);
        else
            return PhysicsCollisionData(true, c + e);
    } else if (other->getType() == PhysicsColliderTypePlane) {
        PhysicsColliderPlane *_other = static_cast<PhysicsColliderPlane *>(other);
        
        if (_other->getNormal() != this->getNormal())
            return PhysicsCollisionData(true, 0);
        else
            return PhysicsCollisionData(false, 0);
    } else if (other->getType() == PhysicsColliderTypeMesh) {
        PhysicsColliderMesh *_other = static_cast<PhysicsColliderMesh *>(other);
        
        glm::vec3 farthestPointAlongNormal = getFarthestPointAlongAxis(_other, this->getNormal()) - this->getPosition();
        glm::vec3 farthestPointAlongOppNormal = getFarthestPointAlongAxis(_other, -this->getNormal()) - this->getPosition();
        
        float distance1 = glm::dot(farthestPointAlongNormal, this->getNormal());
        float distance2 = glm::dot(farthestPointAlongOppNormal, this->getNormal());
        
        if (distance1 > 0 && distance2 > 0)
            return PhysicsCollisionData(true, 0);
    }
    return PhysicsCollisionData(false, 0);
}

} // namespace
