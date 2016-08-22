// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Physics/PhysicsColliderSphere.h>
#include <sunglasses/Physics/PhysicsColliderAABB.h>
#include <sunglasses/Physics/PhysicsColliderPlane.h>
#include <sunglasses/Physics/PhysicsColliderMesh.h>
#include <sunglasses/Physics/GJKAlgorithm.h>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace sunglasses {

PhysicsColliderSphere::PhysicsColliderSphere() {
    setType(PhysicsColliderTypeSphere);
}

PhysicsCollisionData PhysicsColliderSphere::collideWith(PhysicsCollider *other) {
    if (other->getType() == PhysicsColliderTypeSphere) {
        PhysicsColliderSphere *_other = static_cast<PhysicsColliderSphere *>(other);
        float centerDistance = glm::length(this->getPosition() - _other->getPosition());
        float radiusSum = this->getRadius() + _other->getRadius();
        
        glm::vec3 normal = glm::normalize(this->getPosition() - _other->getPosition());
        
        if (radiusSum < centerDistance)
            return PhysicsCollisionData(false, 0);
        else {
            return PhysicsCollisionData(normal, true, centerDistance - radiusSum);
        }
    } else if (other->getType() == PhysicsColliderTypeAABB) {
        PhysicsColliderAABB *_other = static_cast<PhysicsColliderAABB *>(other);
        
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
            return PhysicsCollisionData(true, distance);
        else
            return PhysicsCollisionData(false, distance);
    } else if (other->getType() == PhysicsColliderTypePlane) {
        PhysicsColliderPlane *_other = static_cast<PhysicsColliderPlane *>(other);
        
        float distanceFromCenter = glm::dot(_other->getNormal(), this->getPosition()) - _other->getDistance();
        
        float distanceFromSphere = distanceFromCenter - this->getRadius();
        
        if (distanceFromSphere < 0)
            return PhysicsCollisionData(true, distanceFromSphere);
        else
            return PhysicsCollisionData(false, distanceFromSphere);
    } else if (other->getType() == PhysicsColliderTypeMesh) {
        PhysicsColliderMesh *_other = static_cast<PhysicsColliderMesh *>(other);
        
        Simplex simplex;
        
        glm::vec3 direction = glm::vec3(1, 1, 1);
        glm::vec3 a = support(_other, this, direction, simplex);
        simplex.add(a);
        
        direction = -a;
        
        int max = 10;
        
        for (int i = 0; i < max; i++) {
            glm::vec3 point = support(_other, this, direction, simplex);
            
            if (glm::dot(point, direction) < 0) {
                return PhysicsCollisionData(false, 0);
            } else {
                simplex.add(point);
                
                if (processSimplex(simplex, direction) == true) {
                    return PhysicsCollisionData(true, 0);
                }
            }
        }
    }
    return PhysicsCollisionData(false, 0);
}

} // namespace
