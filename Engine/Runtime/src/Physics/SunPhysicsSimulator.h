// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNPHYSICSSIMULATOR_H
#define    SUNPHYSICSSIMULATOR_H

#include <vector>
#include <tuple>

#include "SunPhysicsWorld.h"
#include "SunPhysicsObject.h"

typedef std::tuple<SunPhysicsObject *, SunPhysicsCollider *, SunPhysicsObject *, SunPhysicsCollider *, SunPhysicsCollisionData> SunPhysicsCollisionTuple;

class SunPhysicsSimulator {
public:

    // Execute the entire physics cycle of the scene
    void cycle(float delta);

    // Move each object to its new position based on the forces acting on it
    void integrate(float delta);
    // Detect objects that collided after integrating
    std::vector<SunPhysicsCollisionTuple> detectCollisions(float delta);
    // Respond to the collisions previously detected
    void respondToCollisions(std::vector<SunPhysicsCollisionTuple> collisions, float delta);

    inline SunPhysicsWorld & getWorld() { return world; }
    inline void setWorld(SunPhysicsWorld _w) { world = _w; }
private:
    SunPhysicsWorld world;
};

#endif
