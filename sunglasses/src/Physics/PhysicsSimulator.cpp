// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Physics/PhysicsSimulator.h>
#include <iostream>

namespace sunglasses {

void PhysicsSimulator::cycle(float delta) {
    integrate(delta);
    std::vector<PhysicsCollisionTuple> collisions = detectCollisions(delta);
    respondToCollisions(collisions, delta);
}

void PhysicsSimulator::integrate(float delta) {
    std::vector<PhysicsForce> forces;
    forces.push_back(world.getGravity());
    for (size_t i = 0; i < world.getObjects().size(); i++) {
        world.getObjectAtIndex(i)->updatePositionForForcesAndDelta(forces, delta);
    }
}

std::vector<PhysicsCollisionTuple> PhysicsSimulator::detectCollisions(float delta) {
    std::vector<PhysicsCollisionTuple> collidingObjects;
    for (size_t i = 0; i < world.getObjects().size(); i++) {
        for (int j = 0; j < world.getObjectAtIndex(i)->getCollidersSize(); j++) {
            if (world.getObjectAtIndex(i)->getSelfCollision() == true) {
                // Check for collisions against other colliders in the object
                for (int k = j + 1; j < world.getObjectAtIndex(i)->getCollidersSize(); k++) {
                    PhysicsCollisionData data = world.getObjectAtIndex(i)->getColliderAtIndex(j)->collideWith(world.getObjectAtIndex(i)->getColliderAtIndex(k));
                    if (data.collided == true) {
                        collidingObjects.push_back(std::make_tuple(world.getObjectAtIndex(i), world.getObjectAtIndex(i)->getColliderAtIndex(j), world.getObjectAtIndex(i), world.getObjectAtIndex(i)->getColliderAtIndex(k), data));
                    }
                }
            }

            // Check for collisions against other colliders in the scene
            for (size_t k = i + 1; k < world.getObjects().size(); k++) {
                for (int l = 0; l < world.getObjectAtIndex(k)->getCollidersSize(); l++) {
                    PhysicsCollisionData data = world.getObjectAtIndex(i)->getColliderAtIndex(j)->collideWith(world.getObjectAtIndex(k)->getColliderAtIndex(l));
                    if (data.collided == true) {
                        collidingObjects.push_back(std::make_tuple(world.getObjectAtIndex(i), world.getObjectAtIndex(i)->getColliderAtIndex(j), world.getObjectAtIndex(k), world.getObjectAtIndex(k)->getColliderAtIndex(l), data));
                    }
                }
            }
        }
    }
    return collidingObjects;
}

void PhysicsSimulator::respondToCollisions(std::vector<PhysicsCollisionTuple> collisions, float delta) {
    for (size_t i = 0; i < collisions.size(); i++) {
        PhysicsObject *first = std::get<0>(collisions[i]);
        PhysicsCollider *firstCollider = std::get<1>(collisions[i]);
        PhysicsObject *second = std::get<2>(collisions[i]);
        PhysicsCollider *secondCollider = std::get<3>(collisions[i]);
        //PhysicsCollisionData data = std::get<4>(collisions[i]);

        // Perfectly Elastic Collision
        if (first->getElasticity() == 1 && second->getElasticity() == 1) {
            bool reflection = false;
            if (firstCollider->getType() == PhysicsColliderTypePlane && ((PhysicsColliderPlane *)firstCollider)->getReflective() == true) {
                reflection = true;
                glm::vec3 normal = ((PhysicsColliderPlane *)firstCollider)->getNormal();
                float magnitude = glm::length(second->getVelocity());
                glm::vec3 initial = second->getVelocity();

                glm::vec3 newVelocity = initial - (2.0f * normal * glm::dot(initial, normal));
                second->setVelocity(glm::normalize(newVelocity) * magnitude);
            }

            if (secondCollider->getType() == PhysicsColliderTypePlane && ((PhysicsColliderPlane *)secondCollider)->getReflective() == true) {
                reflection = true;
                glm::vec3 normal = ((PhysicsColliderPlane *)secondCollider)->getNormal();
                float magnitude = glm::length(first->getVelocity());
                glm::vec3 initial = first->getVelocity();

                glm::vec3 newVelocity = initial - (2.0f * normal * glm::dot(initial, normal));
                first->setVelocity(glm::normalize(newVelocity) * magnitude);
            }

            if (reflection == false) {
                float m1 = first->getMass();
                float m2 = second->getMass();

                // This is the collision normal (line of collision) and the normal of the tangent plane
                glm::vec3 normal = glm::normalize(second->getPosition() - first->getPosition());

                // Get scalar projections onto the normal
                double _v1ns = glm::dot(first->getVelocity(), normal);
                double _v2ns = glm::dot(second->getVelocity(), normal);

                double v1ns = ((1 * m2 * (_v2ns - _v1ns)) / (m1 + m2)) + ((m1 * _v1ns) / (m1 + m2)) + ((m2 * _v2ns) / (m1 + m2));
                double v2ns = ((1 * m1 * (_v1ns - _v2ns)) / (m1 + m2)) + ((m2 * _v2ns) / (m1 + m2)) + ((m1 * _v1ns) / (m1 + m2));

                glm::vec3 v1n = float(v1ns) * normal;
                glm::vec3 v2n = float(v2ns) * normal;

                glm::vec3 v1t = first->getVelocity() - (glm::dot(first->getVelocity(), normal) * normal);
                glm::vec3 v2t = second->getVelocity() - (glm::dot(second->getVelocity(), normal) * normal);

                glm::vec3 v1 = v1n + v1t;
                glm::vec3 v2 = v2n + v2t;

                first->setVelocity(v1);
                second->setVelocity(v2);
            }
        }
    }
}

} // sunglasses
