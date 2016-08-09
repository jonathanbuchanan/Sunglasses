// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef GJKALGORITHM_H
#define GJKALGORITHM_H

#include <sunglasses/Physics/PhysicsColliderMesh.h>
#include <sunglasses/Physics/PhysicsColliderSphere.h>
#include <sunglasses/Physics/PhysicsColliderAABB.h>
#include <sunglasses/Physics/PhysicsColliderPlane.h>

namespace sunglasses {

extern glm::vec3 getFarthestPointAlongAxis(PhysicsColliderMesh *mesh, glm::vec3 axis);
extern glm::vec3 getFarthestPointAlongAxis(PhysicsColliderSphere *sphere, glm::vec3 axis);
extern glm::vec3 getFarthestPointAlongAxis(PhysicsColliderAABB *aabb, glm::vec3 axis);

extern glm::vec3 support(PhysicsColliderMesh *first, PhysicsColliderMesh *second, glm::vec3 axis, Simplex &simplex);
extern glm::vec3 support(PhysicsColliderMesh *first, PhysicsColliderSphere *sphere, glm::vec3 axis, Simplex &simplex);
extern glm::vec3 support(PhysicsColliderMesh *first, PhysicsColliderAABB *aabb, glm::vec3 axis, Simplex &simplex);

extern glm::vec3 tripleCross(glm::vec3 a, glm::vec3 b, glm::vec3 c);

extern bool processLine(Simplex &simplex, glm::vec3 &direction);
extern bool processTriangle(Simplex &simplex, glm::vec3 &direction);
extern bool processTetrahedron(Simplex &simplex, glm::vec3 &direction);

extern bool processSimplex(Simplex &simplex, glm::vec3 &direction);

} // namespace

#endif
