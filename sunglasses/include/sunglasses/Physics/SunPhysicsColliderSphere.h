// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNPHYSICSCOLLIDERSPHERE_H
#define SUNPHYSICSCOLLIDERSPHERE_H

#include <sunglasses/Physics/SunPhysicsCollider.h>

namespace sunglasses {

class SunPhysicsColliderSphere : public SunPhysicsCollider {
public:

    SunPhysicsColliderSphere();

    virtual SunPhysicsCollisionData collideWith(SunPhysicsCollider *other);

    inline float & getRadius() { return radius; }
    inline void setRadius(float _r) { radius = _r; }
private:
    float radius;
};

} // namespace

#endif
