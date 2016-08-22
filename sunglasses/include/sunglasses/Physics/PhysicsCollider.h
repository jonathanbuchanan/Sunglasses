// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef PHYSICSCOLLIDER_H
#define PHYSICSCOLLIDER_H

#include <glm/glm.hpp>

namespace sunglasses {

enum PhysicsColliderType {
    PhysicsColliderTypeAABB,
    PhysicsColliderTypeOBB,
    PhysicsColliderTypeSphere,
    PhysicsColliderTypePlane,
    PhysicsColliderTypeMesh
};

struct PhysicsCollisionData {
    bool collided;
    glm::vec3 normal;
    float distance;
    
    PhysicsCollisionData() {
        collided = false;
        distance = 0;
    }
    
    PhysicsCollisionData(bool _c, float _f) {
        collided = _c;
        distance = _f;
    }
    
    PhysicsCollisionData(glm::vec3 _n, bool _c, float _f) {
        normal = _n;
        collided = _c;
        distance = _f;
    }
};

class PhysicsCollider {
public:
    PhysicsCollider();
    
    virtual PhysicsCollisionData collideWith(PhysicsCollider *other);
    
    inline glm::vec3 & getPosition() { return position; }
    virtual inline void setPosition(glm::vec3 _position) { position = _position; }
    virtual inline void setPositionX(float _x) { position.x = _x; }
    virtual inline void setPositionY(float _y) { position.y = _y; }
    virtual inline void setPositionZ(float _z) { position.z = _z; }
    virtual inline void moveTo(glm::vec3 _position) { position = _position; }
    virtual inline void moveToX(float _x) { position.x = _x; }
    virtual inline void moveToY(float _y) { position.y = _y; }
    virtual inline void moveToZ(float _z) { position.z = _z; }
    
    inline PhysicsColliderType & getType() { return type; }
    inline void setType(PhysicsColliderType _type) { type = _type; }
private:
    glm::vec3 position;
    PhysicsColliderType type;
};

} // namespace

#endif
