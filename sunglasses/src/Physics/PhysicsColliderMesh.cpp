// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Physics/PhysicsColliderMesh.h>
#include <sunglasses/Physics/PhysicsColliderSphere.h>
#include <sunglasses/Physics/PhysicsColliderAABB.h>
#include <sunglasses/Physics/PhysicsColliderPlane.h>
#include <sunglasses/Physics/GJKAlgorithm.h>
#include <iostream>
#include <algorithm>

namespace sunglasses {

PhysicsColliderMesh::PhysicsColliderMesh() {
    setType(PhysicsColliderTypeMesh);
}

void PhysicsColliderMesh::importMeshDataFromFile(std::string file) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(file, aiProcess_JoinIdenticalVertices);
    processAssimpNode(scene->mRootNode, scene);
}

void PhysicsColliderMesh::processAssimpNode(aiNode *node, const aiScene *scene) {
    for (size_t i = 0; i < node->mNumMeshes; i++)
        processAssimpMesh(scene->mMeshes[node->mMeshes[i]], scene);

    for (size_t i = 0; i < node->mNumChildren; i++)
        processAssimpNode(node->mChildren[i], scene);
}

void PhysicsColliderMesh::processAssimpMesh(aiMesh *mesh, const aiScene *scene) {
    for (size_t i = 0; i < mesh->mNumVertices; i++) {
        glm::vec3 vertex;
        vertex.x = mesh->mVertices[i].x;
        vertex.y = mesh->mVertices[i].y;
        vertex.z = mesh->mVertices[i].z;
        Vertex v = Vertex(vertex);
        if (std::find(vertices.begin(), vertices.end(), v) == vertices.end())
            vertices.push_back(v);
    }
}

PhysicsCollisionData PhysicsColliderMesh::collideWith(PhysicsCollider *other) {
    if (other->getType() == PhysicsColliderTypeMesh) {
        PhysicsColliderMesh *_other = static_cast<PhysicsColliderMesh *>(other);

        Simplex simplex;

        glm::vec3 direction = glm::vec3(1, 1, 1);
        glm::vec3 a = support(this, _other, direction, simplex);
        simplex.add(a);

        direction = -a;

        int max = 10;

        for (int i = 0; i < max; i++) {
            glm::vec3 point = support(this, _other, direction, simplex);

            if (glm::dot(point, direction) < 0) {
                return PhysicsCollisionData(false, 0);
            } else {
                simplex.add(point);

                if (processSimplex(simplex, direction) == true) {
                    return PhysicsCollisionData(true, 0);
                }
            }
        }
    } else if (other->getType() == PhysicsColliderTypeSphere) {
        PhysicsColliderSphere *_other = static_cast<PhysicsColliderSphere *>(other);

        Simplex simplex;

        glm::vec3 direction = glm::vec3(1, 1, 1);
        glm::vec3 a = support(this, _other, direction, simplex);
        simplex.add(a);

        direction = -a;

        int max = 10;

        for (int i = 0; i < max; i++) {
            glm::vec3 point = support(this, _other, direction, simplex);

            if (glm::dot(point, direction) < 0) {
                return PhysicsCollisionData(false, 0);
            } else {
                simplex.add(point);

                if (processSimplex(simplex, direction) == true) {
                    return PhysicsCollisionData(true, 0);
                }
            }
        }
    } else if (other->getType() == PhysicsColliderTypeAABB) {
        PhysicsColliderAABB *_other = static_cast<PhysicsColliderAABB *>(other);

        Simplex simplex;

        glm::vec3 direction = glm::vec3(1, 1, 1);
        glm::vec3 a = support(this, _other, direction, simplex);
        simplex.add(a);

        direction = -a;

        int max = 10;

        for (int i = 0; i < max; i++) {
            glm::vec3 point = support(this, _other, direction, simplex);

            if (glm::dot(point, direction) < 0) {
                return PhysicsCollisionData(false, 0);
            } else {
                simplex.add(point);

                if (processSimplex(simplex, direction) == true) {
                    return PhysicsCollisionData(true, 0);
                }
            }
        }
    } else if (other->getType() == PhysicsColliderTypePlane) {
        PhysicsColliderPlane *_other = static_cast<PhysicsColliderPlane *>(other);

        glm::vec3 farthestPointAlongNormal = getFarthestPointAlongAxis(this, _other->getNormal()) - _other->getPosition();
        glm::vec3 farthestPointAlongOppNormal = getFarthestPointAlongAxis(this, -_other->getNormal()) - _other->getPosition();

        float distance1 = glm::dot(farthestPointAlongNormal, _other->getNormal());
        float distance2 = glm::dot(farthestPointAlongOppNormal, -_other->getNormal());

        if (distance1 > 0 && distance2 > 0)
            return PhysicsCollisionData(true, 0);
    }
    return PhysicsCollisionData(false, 0);
}

} // namespace
