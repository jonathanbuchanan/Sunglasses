#include "SunPhysicsColliderMesh.h"
#include "SunPhysicsColliderSphere.h"
#include "GJKAlgorithm.h"
#include <iostream>
#include <algorithm>

SunPhysicsColliderMesh::SunPhysicsColliderMesh() {
    setType(SunPhysicsColliderTypeMesh);
}

void SunPhysicsColliderMesh::importMeshDataFromFile(string file) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(file, aiProcess_JoinIdenticalVertices);
    processAssimpNode(scene->mRootNode, scene);
}

void SunPhysicsColliderMesh::processAssimpNode(aiNode *node, const aiScene *scene) {
    for (int i = 0; i < node->mNumMeshes; i++)
        processAssimpMesh(scene->mMeshes[node->mMeshes[i]], scene);
    
    for (int i = 0; i < node->mNumChildren; i++)
        processAssimpNode(node->mChildren[i], scene);
}

void SunPhysicsColliderMesh::processAssimpMesh(aiMesh *mesh, const aiScene *scene) {
    for (int i = 0; i < mesh->mNumVertices; i++) {
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
    }
    return SunPhysicsCollisionData(false, 0);
}


