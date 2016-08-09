// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef PHYSICSCOLLIDERSPHERE_H
#define PHYSICSCOLLIDERSPHERE_H

#include <sunglasses/Physics/PhysicsCollider.h>

namespace sunglasses {

class PhysicsColliderSphere : public PhysicsCollider {
public:

    PhysicsColliderSphere();

    virtual PhysicsCollisionData collideWith(PhysicsCollider *other);

    inline float & getRadius() { return radius; }
    inline void setRadius(float _r) { radius = _r; }
private:
    float radius;
};

} // namespace

#endif
