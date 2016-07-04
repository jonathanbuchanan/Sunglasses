// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNPHYSICSCOLLIDERMESH_H
#define    SUNPHYSICSCOLLIDERMESH_H

#include <sunglasses/Physics/SunPhysicsCollider.h>
#include <sunglasses/Graphics/SunPrimitives.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class SunPhysicsColliderMesh : public SunPhysicsCollider {
public:
    SunPhysicsColliderMesh();

    void importMeshDataFromFile(std::string file);

    virtual SunPhysicsCollisionData collideWith(SunPhysicsCollider *other);

    inline int getVertexCount() { return vertices.size(); }
    inline glm::vec3 getPositionAtIndex(int i) { return vertices[i].position + getPosition(); }
private:
    void processAssimpNode(aiNode *node, const aiScene *scene);
    void processAssimpMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<SunVertex> vertices;

};

#endif
