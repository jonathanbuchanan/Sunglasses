/* 
 * File:   SunPhysicsObject.h
 * Author: jonathan
 *
 * Created on August 6, 2015, 11:37 AM
 */

#ifndef SUNPHYSICSOBJECT_H
#define	SUNPHYSICSOBJECT_H

#include "SunPhysicsForce.h"
#include "SunPhysicsCollider.h"
#include "SunPhysicsColliderAABB.h"
#include "SunPhysicsColliderSphere.h"

#include <vector>
using namespace std;

class SunPhysicsObject {
public:
    SunPhysicsObject();
    
    void updatePositionForForcesAndDelta(vector<SunPhysicsForce> forces, float delta);
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
    
    inline SunPhysicsCollider * getCollider() { return collider; }
    inline void setCollider(SunPhysicsCollider *_c) { collider = _c; }
private:
    // Position
    glm::vec3 position = glm::vec3(0, 0, 0);
    
    // Velocity
    glm::vec3 velocity = glm::vec3(0, 0, 0);
    
    // Mass (in kilograms)
    float mass = 1;
    
    // Physics Collider
    SunPhysicsCollider *collider;
};

#endif