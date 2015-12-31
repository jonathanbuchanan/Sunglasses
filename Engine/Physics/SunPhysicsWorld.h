/* 
 * File:   SunPhysicsWorld.h
 * Author: jonathan
 *
 * Created on August 14, 2015, 11:25 PM
 */

#ifndef SUNPHYSICSWORLD_H
#define	SUNPHYSICSWORLD_H

#include "SunPhysicsForce.h"
#include "SunPhysicsObject.h"

#include <vector>
using namespace std;

class SunPhysicsWorld {
public:
    SunPhysicsWorld();
    
    inline SunPhysicsForce & getGravity() { return gravity; }
    inline void setGravity(SunPhysicsForce _gravity) { gravity = _gravity; }
    
    inline vector<SunPhysicsObject *> & getObjects() { return objects; }
    inline SunPhysicsObject * getObjectAtIndex(int i) { return objects[i]; }
    inline void addObjectToObjects(SunPhysicsObject *object) { objects.push_back(object); }
private:
    SunPhysicsForce gravity;
    vector<SunPhysicsObject *> objects;
};

#endif

