// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef GJKALGORITHM_H
#define GJKALGORITHM_H

#include <sunglasses/Physics/SunPhysicsColliderMesh.h>
#include <sunglasses/Physics/SunPhysicsColliderSphere.h>
#include <sunglasses/Physics/SunPhysicsColliderAABB.h>
#include <sunglasses/Physics/SunPhysicsColliderPlane.h>

namespace sunglasses {

extern glm::vec3 getFarthestPointAlongAxis(SunPhysicsColliderMesh *mesh, glm::vec3 axis);
extern glm::vec3 getFarthestPointAlongAxis(SunPhysicsColliderSphere *sphere, glm::vec3 axis);
extern glm::vec3 getFarthestPointAlongAxis(SunPhysicsColliderAABB *aabb, glm::vec3 axis);

extern glm::vec3 support(SunPhysicsColliderMesh *first, SunPhysicsColliderMesh *second, glm::vec3 axis, Simplex &simplex);
extern glm::vec3 support(SunPhysicsColliderMesh *first, SunPhysicsColliderSphere *sphere, glm::vec3 axis, Simplex &simplex);
extern glm::vec3 support(SunPhysicsColliderMesh *first, SunPhysicsColliderAABB *aabb, glm::vec3 axis, Simplex &simplex);

extern glm::vec3 tripleCross(glm::vec3 a, glm::vec3 b, glm::vec3 c);

extern bool processLine(Simplex &simplex, glm::vec3 &direction);
extern bool processTriangle(Simplex &simplex, glm::vec3 &direction);
extern bool processTetrahedron(Simplex &simplex, glm::vec3 &direction);

extern bool processSimplex(Simplex &simplex, glm::vec3 &direction);

} // namespace

#endif
