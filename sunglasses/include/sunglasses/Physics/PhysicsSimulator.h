// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef PHYSICSSIMULATOR_H
#define PHYSICSSIMULATOR_H

#include <vector>
#include <tuple>

#include <sunglasses/Physics/PhysicsWorld.h>
#include <sunglasses/Physics/PhysicsObject.h>

namespace sunglasses {

typedef std::tuple<PhysicsObject *, PhysicsCollider *, PhysicsObject *, PhysicsCollider *, PhysicsCollisionData> PhysicsCollisionTuple;

class PhysicsSimulator {
public:

    // Execute the entire physics cycle of the scene
    void cycle(float delta);

    // Move each object to its new position based on the forces acting on it
    void integrate(float delta);
    // Detect objects that collided after integrating
    std::vector<PhysicsCollisionTuple> detectCollisions(float delta);
    // Respond to the collisions previously detected
    void respondToCollisions(std::vector<PhysicsCollisionTuple> collisions, float delta);

    inline PhysicsWorld & getWorld() { return world; }
    inline void setWorld(PhysicsWorld _w) { world = _w; }
private:
    PhysicsWorld world;
};

} // namespace

#endif
