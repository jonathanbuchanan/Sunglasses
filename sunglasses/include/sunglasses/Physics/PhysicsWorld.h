// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include <sunglasses/Physics/PhysicsForce.h>
#include <sunglasses/Physics/PhysicsObject.h>

#include <vector>

namespace sunglasses {

class PhysicsWorld {
public:
    PhysicsWorld();

    inline PhysicsForce & getGravity() { return gravity; }
    inline void setGravity(PhysicsForce _gravity) { gravity = _gravity; }

    inline std::vector<PhysicsObject *> & getObjects() { return objects; }
    inline PhysicsObject * getObjectAtIndex(int i) { return objects[i]; }
    inline void addObjectToObjects(PhysicsObject *object) { objects.push_back(object); }
private:
    PhysicsForce gravity;
    std::vector<PhysicsObject *> objects;
};

} // namespace

#endif
