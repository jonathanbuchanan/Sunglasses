// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef PHYSICSCOLLIDERMESH_H
#define PHYSICSCOLLIDERMESH_H

#include <sunglasses/Physics/PhysicsCollider.h>
#include <sunglasses/Graphics/Primitives.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace sunglasses {

class PhysicsColliderMesh : public PhysicsCollider {
public:
    PhysicsColliderMesh();

    void importMeshDataFromFile(std::string file);

    virtual PhysicsCollisionData collideWith(PhysicsCollider *other);

    inline int getVertexCount() { return vertices.size(); }
    inline glm::vec3 getPositionAtIndex(int i) { return vertices[i].position + getPosition(); }
private:
    void processAssimpNode(aiNode *node, const aiScene *scene);
    void processAssimpMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Vertex> vertices;

};

} // namespace

#endif
