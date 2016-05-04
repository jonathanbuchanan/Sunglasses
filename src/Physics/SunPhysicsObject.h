// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNPHYSICSOBJECT_H
#define    SUNPHYSICSOBJECT_H

#include "SunPhysicsForce.h"
#include "SunPhysicsCollider.h"
#include "SunPhysicsColliderAABB.h"
#include "SunPhysicsColliderSphere.h"
#include "SunPhysicsColliderPlane.h"
#include "SunPhysicsColliderMesh.h"

#include <vector>

class SunPhysicsObject {
public:
    SunPhysicsObject();

    void updatePositionForForcesAndDelta(std::vector<SunPhysicsForce> forces, float delta);
    SunPhysicsCollisionData collideWith(SunPhysicsObject *_other);

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

    inline std::vector<SunPhysicsCollider *> & getColliders() { return colliders; }
    inline int getCollidersSize() { return colliders.size(); }
    inline SunPhysicsCollider * getColliderAtIndex(int i) { return colliders[i]; }
    inline void addCollider(SunPhysicsCollider *c) { colliders.push_back(c); }

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
    std::vector<SunPhysicsCollider *> colliders;

    // Do Self Collision
    bool selfCollision;
};

#endif
