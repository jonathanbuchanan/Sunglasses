/* 
 * File:   SunPhysicsSimulator.h
 * Author: jonathan
 *
 * Created on August 6, 2015, 11:30 AM
 */

#ifndef SUNPHYSICSSIMULATOR_H
#define	SUNPHYSICSSIMULATOR_H

class SunPhysicsSimulator {
public:
    
    // Execute the entire physics cycle of the scene
    void cycle();
    
    // Move each object to its new position based on the forces acting on it
    void integrate();
    // Detect objects that collided after integrating
    void detectCollisions();
    // Respond to the collisions previously detected
    void respondToCollisions();
    
private:
    
};

#endif

