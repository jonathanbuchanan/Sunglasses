/* 
 * File:   SunPhysicsSimulator.h
 * Author: jonathan
 *
 * Created on August 6, 2015, 11:30 AM
 */

#ifndef SUNPHYSICSSIMULATOR_H
#define	SUNPHYSICSSIMULATOR_H

#include "SunPhysicsWorld.h"
#include "SunPhysicsObject.h"

class SunPhysicsSimulator {
public:
    
    // Execute the entire physics cycle of the scene
    void cycle(float delta);
    
    // Move each object to its new position based on the forces acting on it
    void integrate(float delta);
    // Detect objects that collided after integrating
    void detectCollisions(float delta);
    // Respond to the collisions previously detected
    void respondToCollisions(float delta);
    
    inline SunPhysicsWorld & getWorld() { return world; }
    inline void setWorld(SunPhysicsWorld _w) { world = _w; }
private:
    SunPhysicsWorld world;
};

#endif

