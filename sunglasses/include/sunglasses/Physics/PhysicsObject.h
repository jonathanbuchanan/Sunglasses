// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include <sunglasses/Physics/PhysicsForce.h>
#include <sunglasses/Physics/PhysicsCollider.h>
#include <sunglasses/Physics/PhysicsColliderAABB.h>
#include <sunglasses/Physics/PhysicsColliderSphere.h>
#include <sunglasses/Physics/PhysicsColliderPlane.h>
#include <sunglasses/Physics/PhysicsColliderMesh.h>

#include <vector>

namespace sunglasses {

class PhysicsObject {
public:
    PhysicsObject();

    void updatePositionForForcesAndDelta(std::vector<PhysicsForce> forces, float delta);
    PhysicsCollisionData collideWith(PhysicsObject *_other);

    inline glm::vec3 & getPosition() { return position; }
    inline void setPosition(glm::vec3 _position) { position = _position; }
    inline void setPositionX(float x) { position.x = x; }
    inline void setPositionY(float y) { position.y = y; }
    inline void setPositionZ(float z) { position.z = z; }

    inline glm::vec3 & getVelocity() { return velocity; }
    inline void setVelocity(glm::vec3 _velocity) { velocity = _velocity; }
    inline void setVelocityX(float x) { velocity.x = x; }
    inline void setVelocityY(float y) { velocity.y = y; }
    inline void setVelocityZ(float z) { velocity.z = z; }

    inline float & getMass() { return mass; }
    inline void setMass(float _mass) { mass = _mass; }

    inline glm::vec3 getMomentum() { return velocity * mass; }

    inline bool & getStationary() { return stationary; }
    inline void setStationary(bool _s) { stationary = _s; }

    inline float & getElasticity() { return elasticity; }
    inline void setElasticity(float _e) { elasticity = _e; }

    inline std::vector<PhysicsCollider *> & getColliders() { return colliders; }
    inline int getCollidersSize() { return colliders.size(); }
    inline PhysicsCollider * getColliderAtIndex(int i) { return colliders[i]; }
    inline void addCollider(PhysicsCollider *c) { colliders.push_back(c); }

    inline bool & getSelfCollision() { return selfCollision; }
    inline void setSelfCollision(bool s) { selfCollision = s; }
private:
    // Position
    glm::vec3 position = glm::vec3(0, 0, 0);

    // Velocity
    glm::vec3 velocity = glm::vec3(0, 0, 0);

    // Mass (in kilograms)
    float mass = 1;

    // Stationary
    bool stationary = false;

    // Elasticity
    float elasticity;

    // Physics Colliders
    std::vector<PhysicsCollider *> colliders;

    // Do Self Collision
    bool selfCollision;
};

} // namespace

#endif
