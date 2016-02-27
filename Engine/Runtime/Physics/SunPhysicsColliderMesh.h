// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
/*
 * File:   SunPhysicsColliderMesh.h
 * Author: jonathan
 *
 * Created on August 21, 2015, 11:17 PM
 */

#ifndef SUNPHYSICSCOLLIDERMESH_H
#define	SUNPHYSICSCOLLIDERMESH_H

#include "SunPhysicsCollider.h"
#include "../Graphics/SunPrimitives.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

class SunPhysicsColliderMesh : public SunPhysicsCollider {
public:
    SunPhysicsColliderMesh();

    void importMeshDataFromFile(string file);

    virtual SunPhysicsCollisionData collideWith(SunPhysicsCollider *other);

    inline int getVertexCount() { return vertices.size(); }
    inline glm::vec3 getPositionAtIndex(int i) { return vertices[i].position + getPosition(); }
private:
    void processAssimpNode(aiNode *node, const aiScene *scene);
    void processAssimpMesh(aiMesh *mesh, const aiScene *scene);

    vector<SunVertex> vertices;

};

#endif
