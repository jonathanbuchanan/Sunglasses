// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunModelResource.h"

#include "SunMaterialResource.h"
#include "SunMeshResource.h"
#include "SunTextureResource.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>

SunModelResource::SunModelResource(std::string _path) : path(_path), meshMap(nullptr) {

}

SunModelResource::SunModelResource(std::string _path, std::map<std::string, SunResource *> *_meshMap) : path(_path), meshMap(_meshMap) {

}

void SunModelResource::init() {
    scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

    // Add meshes
    if (meshMap != nullptr) {
        // Loop through meshes
        for (size_t i = 0; i < scene->mNumMeshes; i++) {
            // Get mesh
            aiMesh *mesh = scene->mMeshes[i];

            // Get name
            std::string name = std::string(mesh->mName.C_Str());

            // Create mesh resource
            SunMeshResource *meshResource = new SunMeshResource(mesh);

            // Add to the mesh map
            meshMap->insert(std::pair<std::string, SunMeshResource *>(name, meshResource));
        }
    }
}
