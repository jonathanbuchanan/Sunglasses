/* 
 * File:   SunPhysicsColliderPlane.h
 * Author: jonathan
 *
 * Created on August 19, 2015, 12:56 PM
 */

#ifndef SUNPHYSICSCOLLIDERPLANE_H
#define	SUNPHYSICSCOLLIDERPLANE_H

#include "SunPhysicsCollider.h"
#include "glm/glm.hpp"

class SunPhysicsColliderPlane : public SunPhysicsCollider {
public:
    
    SunPhysicsColliderPlane();
    
    virtual SunPhysicsCollisionData collideWith(SunPhysicsCollider *other);
    
    inline glm::vec3 & getNormal() { return normal; }
    inline void setNormal(glm::vec3 _normal) { normal = _normal; }
    inline void setNormalX(float _x) { normal.x = _x; }
    inline void setNormalY(float _y) { normal.y = _y; }
    inline void setNormalZ(float _z) { normal.z = _z; }
    
    inline float & getDistance() { return distance; }
    inline void setDistance(float _distance) { distance = _distance; }
    
    inline bool & getReflective() { return reflective; }
    inline void setReflective(bool r) { reflective = r; }
    
    inline virtual glm::vec3 getPosition() { return glm::normalize(normal) * distance; }
private:
    glm::vec3 normal;
    float distance;
    bool reflective;
};

#endif

