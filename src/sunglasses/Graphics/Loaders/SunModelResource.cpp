// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/Loaders/SunModelResource.h>

#include <sunglasses/Graphics/Loaders/SunMaterialResource.h>
#include <sunglasses/Graphics/Loaders/SunMeshResource.h>
#include <sunglasses/Graphics/Loaders/SunTextureResource.h>

#include <assimp/scene.h>
#include <assimp/postprocess.h>

SunModelResource::SunModelResource(std::string _path) : path(_path), meshMap(nullptr), materialMap(nullptr) {

}

SunModelResource::SunModelResource(std::string _path, std::map<std::string, SunResource *> *_meshMap) : path(_path), meshMap(_meshMap), materialMap(nullptr) {

}

SunModelResource::SunModelResource(std::string _path, std::map<std::string, SunResource *> *_meshMap, std::map<std::string, SunResource *> *_materialMap) : path(_path), meshMap(_meshMap), materialMap(_materialMap) {

}

void SunModelResource::init() {
    scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

    // Add meshes
    if (meshMap != nullptr) {
        // Loop through meshes
        for (size_t i = 0; i < scene->mNumMeshes; ++i) {
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

    // Add materials
    if (materialMap != nullptr) {
        // Loop through materials
        for (size_t i = 0; i < scene->mNumMaterials; ++i) {
            // Get material
            aiMaterial *material = scene->mMaterials[i];

            // Get name
            aiString _name;
            material->Get(AI_MATKEY_NAME, _name);
            std::string name = std::string(_name.C_Str());

            // Create material resource
            SunMaterialResource *materialResource = new SunMaterialResource(material);

            // Add to the material map
            materialMap->insert(std::pair<std::string, SunMaterialResource *>(name, materialResource));
        }
    }
}
