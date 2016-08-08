// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Physics/SunPhysicsCollider.h>

namespace sunglasses {

SunPhysicsCollider::SunPhysicsCollider() {
    
}

SunPhysicsCollisionData SunPhysicsCollider::collideWith(SunPhysicsCollider *other) {
    return SunPhysicsCollisionData();
}

} // namespace
