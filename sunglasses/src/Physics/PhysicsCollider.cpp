// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Physics/PhysicsCollider.h>

namespace sunglasses {

PhysicsCollider::PhysicsCollider() {
    
}

PhysicsCollisionData PhysicsCollider::collideWith(PhysicsCollider *other) {
    return PhysicsCollisionData();
}

} // namespace
