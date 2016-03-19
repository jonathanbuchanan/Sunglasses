// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "GJKAlgorithm.h"
#include <iostream>

glm::vec3 getFarthestPointAlongAxis(SunPhysicsColliderMesh *mesh, glm::vec3 axis) {
    glm::vec3 farthestPoint = mesh->getPositionAtIndex(0);
    float farthestDistance = glm::dot(mesh->getPositionAtIndex(0), axis);
    for (int i = 0; i < mesh->getVertexCount(); i++) {
        float temporaryDistance = glm::dot(mesh->getPositionAtIndex(i), axis);
        if (temporaryDistance > farthestDistance) {
            farthestDistance = temporaryDistance;
            farthestPoint = mesh->getPositionAtIndex(i);
        }
    }
    return farthestPoint;
}

glm::vec3 getFarthestPointAlongAxis(SunPhysicsColliderSphere *sphere, glm::vec3 axis) {
    glm::vec3 localPoint = glm::normalize(axis) * sphere->getRadius();
    glm::vec3 globalPoint = localPoint + sphere->getPosition();

    return globalPoint;
}

glm::vec3 getFarthestPointAlongAxis(SunPhysicsColliderAABB *aabb, glm::vec3 axis) {
    glm::vec3 AABBPoints[8] = {
        glm::vec3(aabb->getSecondPointX(), aabb->getSecondPointY(), aabb->getSecondPointZ()),
        glm::vec3(aabb->getFirstPointX(),  aabb->getSecondPointY(), aabb->getSecondPointZ()),
        glm::vec3(aabb->getSecondPointX(), aabb->getFirstPointY(),  aabb->getSecondPointZ()),
        glm::vec3(aabb->getSecondPointX(), aabb->getSecondPointY(), aabb->getFirstPointZ()),
        glm::vec3(aabb->getFirstPointX(),  aabb->getFirstPointY(),  aabb->getSecondPointZ()),
        glm::vec3(aabb->getFirstPointX(),  aabb->getSecondPointY(), aabb->getFirstPointZ()),
        glm::vec3(aabb->getSecondPointX(), aabb->getFirstPointY(),  aabb->getFirstPointZ()),
        glm::vec3(aabb->getFirstPointX(),  aabb->getFirstPointY(),  aabb->getFirstPointZ())
    };

    glm::vec3 farthestPoint = AABBPoints[0];
    float farthestDistance = glm::dot(AABBPoints[0], axis);
    for (int i = 0; i < 8; i++) {
        float temporaryDistance = glm::dot(AABBPoints[i], axis);
        if (temporaryDistance > farthestDistance) {
            farthestDistance = temporaryDistance;
            farthestPoint = AABBPoints[i];
        }
    }
    return farthestPoint;
}

glm::vec3 support(SunPhysicsColliderMesh *first, SunPhysicsColliderMesh *second, glm::vec3 axis, Simplex &simplex) {
    glm::vec3 firstPoint = getFarthestPointAlongAxis(first, axis);
    glm::vec3 secondPoint = getFarthestPointAlongAxis(second, -axis);

    glm::vec3 result = firstPoint - secondPoint;

    return result;
}

glm::vec3 support(SunPhysicsColliderMesh *first, SunPhysicsColliderSphere *sphere, glm::vec3 axis, Simplex &simplex) {
    glm::vec3 firstPoint = getFarthestPointAlongAxis(first, axis);
    glm::vec3 secondPoint = getFarthestPointAlongAxis(sphere, -axis);

    glm::vec3 result = firstPoint - secondPoint;

    return result;
}

glm::vec3 support(SunPhysicsColliderMesh *first, SunPhysicsColliderAABB *aabb, glm::vec3 axis, Simplex &simplex) {
    glm::vec3 firstPoint = getFarthestPointAlongAxis(first, axis);
    glm::vec3 secondPoint = getFarthestPointAlongAxis(aabb, -axis);

    glm::vec3 result = firstPoint - secondPoint;

    return result;
}

glm::vec3 tripleCross(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
    return a * b * c;
}

bool processLine(Simplex &simplex, glm::vec3 &direction) {
    glm::vec3 a = simplex.a;
    glm::vec3 b = simplex.b;
    glm::vec3 ao = -a;
    glm::vec3 ab = b - a;
    glm::vec3 abPerp = glm::cross(glm::cross(ab, ao), ab);

    direction = abPerp;
    return false;
}

bool processTriangle(Simplex &simplex, glm::vec3 &direction) {
    glm::vec3 a = simplex.a;
    glm::vec3 b = simplex.b;
    glm::vec3 c = simplex.c;
    glm::vec3 ao = -a;
    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;
    glm::vec3 abc = glm::cross(ab, ac);
    glm::vec3 abPerp = glm::cross(ab, abc);
    glm::vec3 acPerp = glm::cross(abc, ac);

    bool firstFailed = false;
    bool secondFailed = false;

    if (glm::dot(abPerp, ao) > 0) {
        simplex.set(a, b);
        direction = tripleCross(ab, ao, ab);
    } else {
        firstFailed = true;
    }

    if (glm::dot(acPerp, ao) > 0) {
        simplex.set(a, c);
        direction = tripleCross(ac, ao, ac);
    } else {
        secondFailed = true;
    }

    if (firstFailed == true && secondFailed == true) {
        if (glm::dot(abc, ao) > 0) {
            direction = abc;
        } else {
            simplex.set(a, c, b);
            direction = -abc;
        }
    }

    return false;
}

bool processTetrahedron(Simplex &simplex, glm::vec3 &direction) {
    glm::vec3 a = simplex.a;
    glm::vec3 b = simplex.b;
    glm::vec3 c = simplex.c;
    glm::vec3 d = simplex.d;
    glm::vec3 ao = -a;
    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;
    glm::vec3 ad = d - a;
    glm::vec3 abc = glm::cross(ab, ac);
    glm::vec3 acd = glm::cross(ac, ad);
    glm::vec3 adb = glm::cross(ad, ab);

    bool collision = true;

    if (glm::dot(abc, ao) > 0) {
        collision = false;
    }

    if (glm::dot(acd, ao) > 0) {
        simplex.set(a, c, d);
        collision = false;
    }

    if (glm::dot(adb, ao) > 0) {
        simplex.set(a, d, b);
        collision = false;
    }

    if (collision)
        return true;

    a = simplex.a;
    b = simplex.b;
    c = simplex.c;
    d = simplex.d;
    ao = -a;
    ab = b - a;
    ac = c - a;
    ad = d - a;
    abc = glm::cross(ab, ac);

    bool done = false;

    if (glm::dot(ab, abc) > 0) {
        simplex.set(a, b);
        direction = tripleCross(ab, ao, ab);
        done = true;
    }

    if (glm::dot(abc, ac) > 0) {
        simplex.set(a, c);
        direction = tripleCross(ac, ao, ac);
        done = true;
    }

    if (!done) {
        simplex.set(a, b, c);
        direction = abc;
    }

    return false;
}

bool processSimplex(Simplex &simplex, glm::vec3 &direction) {
    if (simplex.size == 2)
        return processLine(simplex, direction);
    else if (simplex.size == 3)
        return processTriangle(simplex, direction);
    else if (simplex.size == 4)
        return processTetrahedron(simplex, direction);
    return false;
}
