#include "SunPhysicsColliderPlane.h"
#include "SunPhysicsColliderAABB.h"
#include "SunPhysicsColliderSphere.h"
#include "glm/gtx/simd_vec4.hpp"

SunPhysicsColliderPlane::SunPhysicsColliderPlane() {
    setType(SunPhysicsColliderTypePlane);
}

SunPhysicsCollisionData SunPhysicsColliderPlane::collideWith(SunPhysicsCollider *other) {
    if (other->getType() == SunPhysicsColliderTypeSphere) {
        SunPhysicsColliderSphere *_other = static_cast<SunPhysicsColliderSphere *>(other);
        
        float distanceFromCenter = glm::dot(this->getNormal(), _other->getPosition()) - this->getDistance();
        
        float distanceFromSphere = distanceFromCenter - _other->getRadius();
        
        if (distanceFromSphere < 0)
            return SunPhysicsCollisionData(true, distanceFromSphere);
        else
            return SunPhysicsCollisionData(false, distanceFromSphere);
    } else if (other->getType() == SunPhysicsColliderTypeAABB) {
        
    } else if (other->getType() == SunPhysicsColliderTypePlane) {
        SunPhysicsColliderPlane *_other = static_cast<SunPhysicsColliderPlane *>(other);
        
        if (_other->getNormal() != this->getNormal())
            return SunPhysicsCollisionData(true, 0);
        else
            return SunPhysicsCollisionData(false, 0);
    }
    return SunPhysicsCollisionData(false, 0);
}