#include "SunPhysicsColliderOBB.h"

SunPhysicsColliderOBB::SunPhysicsColliderOBB()  {
    setType(SunPhysicsColliderTypeOBB);
}

SunPhysicsCollisionData SunPhysicsColliderOBB::collideWith(SunPhysicsCollider *other) {
    return SunPhysicsCollisionData(false, 0);
}