/* 
 * File:   SunPhysicsColliderOBB.h
 * Author: jonathan
 *
 * Created on August 20, 2015, 9:42 PM
 */

#ifndef SUNPHYSICSCOLLIDEROBB_H
#define	SUNPHYSICSCOLLIDEROBB_H

#include "SunPhysicsCollider.h"

class SunPhysicsColliderOBB : public SunPhysicsCollider {
public:
    
    SunPhysicsColliderOBB();
    
    virtual SunPhysicsCollisionData collideWith(SunPhysicsCollider *other);
    
private:
    
    
    
};

#endif

