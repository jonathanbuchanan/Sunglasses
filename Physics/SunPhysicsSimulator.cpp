#include "SunPhysicsSimulator.h"
#include <iostream>

void SunPhysicsSimulator::cycle(float delta) {
    integrate(delta);
    vector<std::tuple<SunPhysicsObject *, SunPhysicsObject *, SunPhysicsCollisionData>> collisions = detectCollisions(delta);
    respondToCollisions(collisions, delta);
}

void SunPhysicsSimulator::integrate(float delta) {
    vector<SunPhysicsForce> forces;
    forces.push_back(world.getGravity());
    for (int i = 0; i < world.getObjects().size(); i++) {
        world.getObjectAtIndex(i)->updatePositionForForcesAndDelta(forces, delta);
    }
}

vector<std::tuple<SunPhysicsObject *, SunPhysicsObject *, SunPhysicsCollisionData>> SunPhysicsSimulator::detectCollisions(float delta) {
    vector<std::tuple<SunPhysicsObject *, SunPhysicsObject *, SunPhysicsCollisionData>> collidingObjects;
    for (int i = 0; i < world.getObjects().size(); i++) {
        for (int j = i + 1; j < world.getObjects().size(); j++) {
            SunPhysicsCollisionData data = world.getObjectAtIndex(i)->collideWith(world.getObjectAtIndex(j));
            if (data.collided == true) {
                collidingObjects.push_back(std::make_tuple(world.getObjectAtIndex(i), world.getObjectAtIndex(j), data));
            }
        }
    }
    return collidingObjects;
}

void SunPhysicsSimulator::respondToCollisions(vector<std::tuple<SunPhysicsObject *, SunPhysicsObject *, SunPhysicsCollisionData>> collisions, float delta) {
    for (int i = 0; i < collisions.size(); i++) {
        SunPhysicsObject *first = std::get<0>(collisions[i]);
        SunPhysicsObject *second = std::get<1>(collisions[i]);
        
        // Perfectly Elastic Collision
        if (first->getElasticity() == 1 && second->getElasticity() == 1) {
            glm::vec3 firstNew;
            glm::vec3 secondNew;
            
            glm::vec3 x = first->getPosition() - second->getPosition();
            x = glm::normalize(x);
            
            glm::vec3 v1 = first->getVelocity();
            float x1 = glm::dot(x, v1);
            glm::vec3 v1x = x * x1;
            glm::vec3 v1y = v1 - v1x;
            float m1 = first->getMass();
            
            x = x * -1.0f;
            glm::vec3 v2 = second->getVelocity();
            float x2 = glm::dot(x, v2);
            glm::vec3 v2x = x * x2;
            glm::vec3 v2y = v2 - v2x;
            float m2 = second->getMass();
            
            firstNew = (v1x * ((m1 - m2) / (m1 + m2))) + (v2x * ((2 * m2) / (m1 + m2))) + v1y;
            secondNew = (v1x * ((2 * m1) / (m1 + m2))) + (v2x * ((m1 - m2) / (m1 + m2))) + v1y;
            
            first->setVelocity(firstNew);
            second->setVelocity(secondNew);
        }
    }
}