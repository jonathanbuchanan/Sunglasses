// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNPHYSICSWORLD_H
#define SUNPHYSICSWORLD_H

#include <sunglasses/Physics/SunPhysicsForce.h>
#include <sunglasses/Physics/SunPhysicsObject.h>

#include <vector>

namespace sunglasses {

class SunPhysicsWorld {
public:
    SunPhysicsWorld();

    inline SunPhysicsForce & getGravity() { return gravity; }
    inline void setGravity(SunPhysicsForce _gravity) { gravity = _gravity; }

    inline std::vector<SunPhysicsObject *> & getObjects() { return objects; }
    inline SunPhysicsObject * getObjectAtIndex(int i) { return objects[i]; }
    inline void addObjectToObjects(SunPhysicsObject *object) { objects.push_back(object); }
private:
    SunPhysicsForce gravity;
    std::vector<SunPhysicsObject *> objects;
};

} // namespace

#endif
