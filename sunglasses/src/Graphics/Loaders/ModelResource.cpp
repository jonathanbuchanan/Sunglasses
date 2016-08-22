// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/Loaders/ModelResource.h>

#include <sunglasses/Graphics/Loaders/MaterialResource.h>
#include <sunglasses/Graphics/Loaders/MeshResource.h>
#include <sunglasses/Graphics/Loaders/TextureResource.h>

#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace sunglasses {

ModelResource::ModelResource(std::string _path) : path(_path), meshMap(nullptr), materialMap(nullptr) {

}

ModelResource::ModelResource(std::string _path, std::map<std::string, Resource *> *_meshMap) : path(_path), meshMap(_meshMap), materialMap(nullptr) {

}

ModelResource::ModelResource(std::string _path, std::map<std::string, Resource *> *_meshMap, std::map<std::string, Resource *> *_materialMap) : path(_path), meshMap(_meshMap), materialMap(_materialMap) {

}

void ModelResource::init() {
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
            MeshResource *meshResource = new MeshResource(mesh);

            // Add to the mesh map
            meshMap->insert(std::pair<std::string, MeshResource *>(name, meshResource));
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
            MaterialResource *materialResource = new MaterialResource(material);

            // Add to the material map
            materialMap->insert(std::pair<std::string, MaterialResource *>(name, materialResource));
        }
    }
}

} // namespace
