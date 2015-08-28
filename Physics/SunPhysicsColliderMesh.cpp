#include "SunPhysicsColliderMesh.h"
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

glm::vec3 tripleCross(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
    return a * b * c;
}

SunPhysicsCollisionData SunPhysicsColliderMesh::collideWith(SunPhysicsCollider *other) {
    if (other->getType() == SunPhysicsColliderTypeMesh) {
        SunPhysicsColliderMesh *_other = static_cast<SunPhysicsColliderMesh *>(other);
        
        Simplex simplex;
        
        glm::vec3 direction = glm::vec3(1, 1, 1);
        glm::vec3 a = support(_other, direction, simplex);
        simplex.add(a);
        
        direction = -a;
        
        int max = 10;
        
        for (int i = 0; i < max; i++) {
            glm::vec3 point = support(_other, direction, simplex);
            
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

bool SunPhysicsColliderMesh::processSimplex(Simplex &simplex, glm::vec3 &direction) {
    if (simplex.size == 2)
        return processLine(simplex, direction);
    else if (simplex.size == 3)
        return processTriangle(simplex, direction);
    else if (simplex.size == 4)
        return processTetrahedron(simplex, direction);
    return false;
}

bool SunPhysicsColliderMesh::processLine(Simplex &simplex, glm::vec3 &direction) {
    glm::vec3 a = simplex.a;
    glm::vec3 b = simplex.b;
    glm::vec3 ao = -a;
    glm::vec3 ab = b - a;
    glm::vec3 abPerp = glm::cross(glm::cross(ab, ao), ab);
    
    direction = abPerp;
    return false;
}

bool SunPhysicsColliderMesh::processTriangle(Simplex &simplex, glm::vec3 &direction) {
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

bool SunPhysicsColliderMesh::processTetrahedron(Simplex &simplex, glm::vec3 &direction) {
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
    glm::vec3 bcd = glm::cross(c - b, d - b);
    
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

glm::vec3 SunPhysicsColliderMesh::support(SunPhysicsColliderMesh *other, glm::vec3 axis, Simplex &simplex) {
    pair<glm::vec3, int> first = this->getFarthestPointAlongAxis(axis);
    pair<glm::vec3, int> second = other->getFarthestPointAlongAxis(-axis);
    
    glm::vec3 result = first.first - second.first;
    
    return result;
}

pair<glm::vec3, int> SunPhysicsColliderMesh::getFarthestPointAlongAxis(glm::vec3 axis) {
    glm::vec3 farthestPoint = getPositionAtIndex(0);
    float farthestDistance = glm::dot(getPositionAtIndex(0), axis);
    int index = 0;
    for (int i = 0; i < vertices.size(); i++) {
        float temporaryDistance = glm::dot(getPositionAtIndex(i), axis);
        if (temporaryDistance > farthestDistance) {
            farthestDistance = temporaryDistance;
            farthestPoint = getPositionAtIndex(i);
            index = i;
        }
    }
    return pair<glm::vec3, int>(farthestPoint, index);
}

pair<glm::vec3, int> SunPhysicsColliderMesh::getFarthestPointAlongAxis(glm::vec3 axis, vector<int> removedIndices) {
    glm::mat4 matrix;
    glm::translate(matrix, getPosition());
    glm::vec3 transposed = glm::transpose(glm::mat3(matrix)) * axis;
    glm::vec3 farthestPoint;
    float farthestDistance = glm::dot(getPositionAtIndex(0), axis);
    int index = 0;
    for (int i = 0; i < vertices.size(); i++) {
        for (int j = 0; j < removedIndices.size(); j++)
            if (i == removedIndices[j])
                continue;
        float temporaryDistance = glm::dot(getPositionAtIndex(i), transposed);
        if (temporaryDistance > farthestDistance) {
            farthestDistance = temporaryDistance;
            farthestPoint = getPositionAtIndex(i);
            index = i;
        }
    }
    return pair<glm::vec3, int>(farthestPoint, index);
}