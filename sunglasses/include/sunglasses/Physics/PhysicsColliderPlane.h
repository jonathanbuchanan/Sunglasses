// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef PHYSICSCOLLIDERPLANE_H
#define PHYSICSCOLLIDERPLANE_H

#include <sunglasses/Physics/PhysicsCollider.h>
#include <glm/glm.hpp>

namespace sunglasses {

class PhysicsColliderPlane : public PhysicsCollider {
public:

    PhysicsColliderPlane();

    virtual PhysicsCollisionData collideWith(PhysicsCollider *other);

    inline glm::vec3 & getNormal() { return normal; }
    inline void setNormal(glm::vec3 _normal) { normal = _normal; }
    inline void setNormalX(float _x) { normal.x = _x; }
    inline void setNormalY(float _y) { normal.y = _y; }
    inline void setNormalZ(float _z) { normal.z = _z; }

    inline float & getDistance() { return distance; }
    inline void setDistance(float _distance) { distance = _distance; }

    inline bool & getReflective() { return reflective; }
    inline void setReflective(bool r) { reflective = r; }

    inline virtual glm::vec3 getPosition() { return glm::normalize(normal) * distance; }
private:
    glm::vec3 normal;
    float distance;
    bool reflective;
};

} // namespace

#endif
