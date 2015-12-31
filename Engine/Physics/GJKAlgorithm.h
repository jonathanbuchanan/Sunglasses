/* 
 * File:   GJKAlgorithm.h
 * Author: jonathan
 *
 * Created on August 28, 2015, 6:27 PM
 */

#ifndef GJKALGORITHM_H
#define	GJKALGORITHM_H

#include "SunPhysicsColliderMesh.h"
#include "SunPhysicsColliderSphere.h"
#include "SunPhysicsColliderAABB.h"
#include "SunPhysicsColliderPlane.h"

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

#endif

