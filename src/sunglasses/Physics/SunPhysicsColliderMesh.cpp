// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Physics/SunPhysicsColliderMesh.h>
#include <sunglasses/Physics/SunPhysicsColliderSphere.h>
#include <sunglasses/Physics/SunPhysicsColliderAABB.h>
#include <sunglasses/Physics/SunPhysicsColliderPlane.h>
#include <sunglasses/Physics/GJKAlgorithm.h>
#include <iostream>
#include <algorithm>

SunPhysicsColliderMesh::SunPhysicsColliderMesh() {
    setType(SunPhysicsColliderTypeMesh);
}

void SunPhysicsColliderMesh::importMeshDataFromFile(std::string file) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(file, aiProcess_JoinIdenticalVertices);
    processAssimpNode(scene->mRootNode, scene);
}

void SunPhysicsColliderMesh::processAssimpNode(aiNode *node, const aiScene *scene) {
    for (size_t i = 0; i < node->mNumMeshes; i++)
        processAssimpMesh(scene->mMeshes[node->mMeshes[i]], scene);

    for (size_t i = 0; i < node->mNumChildren; i++)
        processAssimpNode(node->mChildren[i], scene);
}

void SunPhysicsColliderMesh::processAssimpMesh(aiMesh *mesh, const aiScene *scene) {
    for (size_t i = 0; i < mesh->mNumVertices; i++) {
        glm::vec3 vertex;
        vertex.x = mesh->mVertices[i].x;
        vertex.y = mesh->mVertices[i].y;
        vertex.z = mesh->mVertices[i].z;
        SunVertex v = SunVertex(vertex);
        if (std::find(vertices.begin(), vertices.end(), v) == vertices.end())
            vertices.push_back(v);
    }
}

SunPhysicsCollisionData SunPhysicsColliderMesh::collideWith(SunPhysicsCollider *other) {
    if (other->getType() == SunPhysicsColliderTypeMesh) {
        SunPhysicsColliderMesh *_other = static_cast<SunPhysicsColliderMesh *>(other);

        Simplex simplex;

        glm::vec3 direction = glm::vec3(1, 1, 1);
        glm::vec3 a = support(this, _other, direction, simplex);
        simplex.add(a);

        direction = -a;

        int max = 10;

        for (int i = 0; i < max; i++) {
            glm::vec3 point = support(this, _other, direction, simplex);

            if (glm::dot(point, direction) < 0) {
                return SunPhysicsCollisionData(false, 0);
            } else {
                simplex.add(point);

                if (processSimplex(simplex, direction) == true) {
                    return SunPhysicsCollisionData(true, 0);
                }
            }
        }
    } else if (other->getType() == SunPhysicsColliderTypeSphere) {
        SunPhysicsColliderSphere *_other = static_cast<SunPhysicsColliderSphere *>(other);

        Simplex simplex;

        glm::vec3 direction = glm::vec3(1, 1, 1);
        glm::vec3 a = support(this, _other, direction, simplex);
        simplex.add(a);

        direction = -a;

        int max = 10;

        for (int i = 0; i < max; i++) {
            glm::vec3 point = support(this, _other, direction, simplex);

            if (glm::dot(point, direction) < 0) {
                return SunPhysicsCollisionData(false, 0);
            } else {
                simplex.add(point);

                if (processSimplex(simplex, direction) == true) {
                    return SunPhysicsCollisionData(true, 0);
                }
            }
        }
    } else if (other->getType() == SunPhysicsColliderTypeAABB) {
        SunPhysicsColliderAABB *_other = static_cast<SunPhysicsColliderAABB *>(other);

        Simplex simplex;

        glm::vec3 direction = glm::vec3(1, 1, 1);
        glm::vec3 a = support(this, _other, direction, simplex);
        simplex.add(a);

        direction = -a;

        int max = 10;

        for (int i = 0; i < max; i++) {
            glm::vec3 point = support(this, _other, direction, simplex);

            if (glm::dot(point, direction) < 0) {
                return SunPhysicsCollisionData(false, 0);
            } else {
                simplex.add(point);

                if (processSimplex(simplex, direction) == true) {
                    return SunPhysicsCollisionData(true, 0);
                }
            }
        }
    } else if (other->getType() == SunPhysicsColliderTypePlane) {
        SunPhysicsColliderPlane *_other = static_cast<SunPhysicsColliderPlane *>(other);

        glm::vec3 farthestPointAlongNormal = getFarthestPointAlongAxis(this, _other->getNormal()) - _other->getPosition();
        glm::vec3 farthestPointAlongOppNormal = getFarthestPointAlongAxis(this, -_other->getNormal()) - _other->getPosition();

        float distance1 = glm::dot(farthestPointAlongNormal, _other->getNormal());
        float distance2 = glm::dot(farthestPointAlongOppNormal, -_other->getNormal());

        if (distance1 > 0 && distance2 > 0)
            return SunPhysicsCollisionData(true, 0);
    }
    return SunPhysicsCollisionData(false, 0);
}
