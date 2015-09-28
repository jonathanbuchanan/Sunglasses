/* 
 * File:   SunPhysicsColliderSphere.h
 * Author: jonathan
 *
 * Created on August 18, 2015, 11:35 PM
 */

#ifndef SUNPHYSICSCOLLIDERSPHERE_H
#define	SUNPHYSICSCOLLIDERSPHERE_H

#include "SunPhysicsCollider.h"

class SunPhysicsColliderSphere : public SunPhysicsCollider {
public:
    
    SunPhysicsColliderSphere();
    
    virtual SunPhysicsCollisionData collideWith(SunPhysicsCollider *other);
    
    inline float & getRadius() { return radius; }
    inline void setRadius(float _r) { radius = _r; }
private:
    float radius;
};

#endif
