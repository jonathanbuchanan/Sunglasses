// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Physics/SunPhysicsColliderSphere.h>
#include <sunglasses/Physics/SunPhysicsColliderAABB.h>
#include <sunglasses/Physics/SunPhysicsColliderPlane.h>
#include <sunglasses/Physics/SunPhysicsColliderMesh.h>
#include <sunglasses/Physics/GJKAlgorithm.h>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

SunPhysicsColliderSphere::SunPhysicsColliderSphere() {
    setType(SunPhysicsColliderTypeSphere);
}

SunPhysicsCollisionData SunPhysicsColliderSphere::collideWith(SunPhysicsCollider *other) {
    if (other->getType() == SunPhysicsColliderTypeSphere) {
        SunPhysicsColliderSphere *_other = static_cast<SunPhysicsColliderSphere *>(other);
        float centerDistance = glm::length(this->getPosition() - _other->getPosition());
        float radiusSum = this->getRadius() + _other->getRadius();
        
        glm::vec3 normal = glm::normalize(this->getPosition() - _other->getPosition());
        
        if (radiusSum < centerDistance)
            return SunPhysicsCollisionData(false, 0);
        else {
            return SunPhysicsCollisionData(normal, true, centerDistance - radiusSum);
        }
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
    } else if (other->getType() == SunPhysicsColliderTypePlane) {
        SunPhysicsColliderPlane *_other = static_cast<SunPhysicsColliderPlane *>(other);
        
        float distanceFromCenter = glm::dot(_other->getNormal(), this->getPosition()) - _other->getDistance();
        
        float distanceFromSphere = distanceFromCenter - this->getRadius();
        
        if (distanceFromSphere < 0)
            return SunPhysicsCollisionData(true, distanceFromSphere);
        else
            return SunPhysicsCollisionData(false, distanceFromSphere);
    } else if (other->getType() == SunPhysicsColliderTypeMesh) {
        SunPhysicsColliderMesh *_other = static_cast<SunPhysicsColliderMesh *>(other);
        
        Simplex simplex;
        
        glm::vec3 direction = glm::vec3(1, 1, 1);
        glm::vec3 a = support(_other, this, direction, simplex);
        simplex.add(a);
        
        direction = -a;
        
        int max = 10;
        
        for (int i = 0; i < max; i++) {
            glm::vec3 point = support(_other, this, direction, simplex);
            
            if (glm::dot(point, direction) < 0) {
                return SunPhysicsCollisionData(false, 0);
            } else {
                simplex.add(point);
                
                if (processSimplex(simplex, direction) == true) {
                    return SunPhysicsCollisionData(true, 0);
                }
            }
        }
    }
    return SunPhysicsCollisionData(false, 0);
}
