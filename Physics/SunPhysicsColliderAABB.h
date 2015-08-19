/* 
 * File:   SunPhysicsColliderAABB.h
 * Author: jonathan
 *
 * Created on August 18, 2015, 10:13 AM
 */

#ifndef SUNPHYSICSCOLLIDERAABB_H
#define	SUNPHYSICSCOLLIDERAABB_H

#include "SunPhysicsCollider.h"

class SunPhysicsColliderAABB : public SunPhysicsCollider {
public:
    
    SunPhysicsColliderAABB();
    
    virtual SunPhysicsCollisionData collideWith(SunPhysicsCollider *other);
    
    inline glm::vec3 & getFirstPoint() { return firstPoint; }
    inline void setFirstPoint(glm::vec3 _f) { firstPoint = _f; }
    inline void setFirstPointX(float _x) { firstPoint.x = _x; }
    inline void setFirstPointY(float _y) { firstPoint.y = _y; }
    inline void setFirstPointZ(float _z) { firstPoint.z = _z; }
    
    inline glm::vec3 & getSecondPoint() { return secondPoint; }
    inline void setSecondPoint(glm::vec3 _s) { secondPoint = _s; }
    inline void setSecondPointX(float _x) { secondPoint.x = _x; }
    inline void setSecondPointY(float _y) { secondPoint.y = _y; }
    inline void setSecondPointZ(float _z) { secondPoint.z = _z; }
    
    virtual inline void moveTo(glm::vec3 _position) { firstPoint += _position - getPosition(); secondPoint += _position - getPosition(); setPosition(_position); }
    virtual inline void moveToX(float _x) { firstPoint.x += _x - getPosition().x; secondPoint.x += _x - getPosition().x; setPositionX(_x); }
    virtual inline void moveToY(float _y) { firstPoint.y += _y - getPosition().y; secondPoint.y += _y - getPosition().y; setPositionX(_y); }
    virtual inline void moveToZ(float _z) { firstPoint.z += _z - getPosition().z; secondPoint.z += _z - getPosition().z; setPositionX(_z); }
private:
    glm::vec3 firstPoint;
    glm::vec3 secondPoint;
};

#endif

