// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
/* 
 * File:   SunPhysicsCollider.h
 * Author: jonathan
 *
 * Created on August 6, 2015, 11:37 AM
 */

#ifndef SUNPHYSICSCOLLIDER_H
#define	SUNPHYSICSCOLLIDER_H

#include "glm/glm.hpp"

enum SunPhysicsColliderType {
    SunPhysicsColliderTypeAABB,
    SunPhysicsColliderTypeOBB,
    SunPhysicsColliderTypeSphere,
    SunPhysicsColliderTypePlane,
    SunPhysicsColliderTypeMesh
};

struct SunPhysicsCollisionData {
    bool collided;
    glm::vec3 normal;
    float distance;
    
    SunPhysicsCollisionData() {
        collided = false;
        distance = 0;
    }
    
    SunPhysicsCollisionData(bool _c, float _f) {
        collided = _c;
        distance = _f;
    }
    
    SunPhysicsCollisionData(glm::vec3 _n, bool _c, float _f) {
        normal = _n;
        collided = _c;
        distance = _f;
    }
};

class SunPhysicsCollider {
public:
    SunPhysicsCollider();
    
    virtual SunPhysicsCollisionData collideWith(SunPhysicsCollider *other);
    
    inline glm::vec3 & getPosition() { return position; }
    virtual inline void setPosition(glm::vec3 _position) { position = _position; }
    virtual inline void setPositionX(float _x) { position.x = _x; }
    virtual inline void setPositionY(float _y) { position.y = _y; }
    virtual inline void setPositionZ(float _z) { position.z = _z; }
    virtual inline void moveTo(glm::vec3 _position) { position = _position; }
    virtual inline void moveToX(float _x) { position.x = _x; }
    virtual inline void moveToY(float _y) { position.y = _y; }
    virtual inline void moveToZ(float _z) { position.z = _z; }
    
    inline SunPhysicsColliderType & getType() { return type; }
    inline void setType(SunPhysicsColliderType _type) { type = _type; }
private:
    glm::vec3 position;
    SunPhysicsColliderType type;
};

#endif

