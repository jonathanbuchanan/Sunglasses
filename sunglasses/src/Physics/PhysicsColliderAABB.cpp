// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Physics/PhysicsColliderAABB.h>
#include <sunglasses/Physics/PhysicsColliderSphere.h>
#include <sunglasses/Physics/PhysicsColliderPlane.h>
#include <sunglasses/Physics/PhysicsColliderMesh.h>
#include <sunglasses/Physics/GJKAlgorithm.h>

#include <glm/gtx/simd_vec4.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/simd_quat.hpp>

#include <string>
#include <iostream>

namespace sunglasses {

PhysicsColliderAABB::PhysicsColliderAABB() {
    setType(PhysicsColliderTypeAABB);
}

PhysicsCollisionData PhysicsColliderAABB::collideWith(PhysicsCollider *other) {
    if (other->getType() == PhysicsColliderTypeAABB) {
        PhysicsColliderAABB *_other = static_cast<PhysicsColliderAABB *>(other);
        glm::vec3 first = this->getFirstPoint() - _other->getSecondPoint();
        glm::vec3 second = _other->getFirstPoint() - this->getSecondPoint();
        
        if (glm::length(first) < glm::length(second)) {
            if (_other->getSecondPoint().x < this->getFirstPoint().x || _other->getSecondPoint().y < this->getFirstPoint().y || _other->getSecondPoint().z < this->getFirstPoint().z)
                return PhysicsCollisionData(false, 0);
            else
                return PhysicsCollisionData(true, glm::length(first));
        } else {
            if (this->getSecondPoint().x < _other->getFirstPoint().x || this->getSecondPoint().y < _other->getFirstPoint().y || this->getSecondPoint().z < _other->getSecondPoint().z)
                return PhysicsCollisionData(false, 0);
            else
                return PhysicsCollisionData(true, glm::length(second));
        }
    } else if (other->getType() == PhysicsColliderTypeSphere) {
        PhysicsColliderSphere *_other = static_cast<PhysicsColliderSphere *>(other);
        
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
            return PhysicsCollisionData(true, distance);
        else
            return PhysicsCollisionData(false, distance);
    } else if (other->getType() == PhysicsColliderTypePlane) {
        PhysicsColliderPlane *_other = static_cast<PhysicsColliderPlane *>(other);
        
        glm::vec3 absoluteNormal = glm::vec3(glm::abs(_other->getNormal().x), glm::abs(_other->getNormal().y), glm::abs(_other->getNormal().z));
        glm::vec3 extents = 0.5f * (this->getSecondPoint() - this->getFirstPoint());
        
        float c = glm::dot(this->getPosition(), _other->getNormal());
        float e = glm::dot(extents, absoluteNormal);
        if (_other->getDistance() < c - e || _other->getDistance() > c + e)
            return PhysicsCollisionData(false, c + e);
        else
            return PhysicsCollisionData(true, c + e);
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
