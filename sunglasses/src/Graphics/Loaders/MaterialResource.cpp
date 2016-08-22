// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/Loaders/MaterialResource.h>

#include <sunglasses/Graphics/Loaders/TextureResource.h>
#include <sunglasses/Graphics/Shader.h>

namespace sunglasses {

MaterialResource::MaterialResource(aiMaterial *_material) : material(_material) {

}

MaterialResource::MaterialResource(glm::vec3 color, float _shininess) : material(nullptr), diffuse(color), specular(color), ambient(color), shininess(_shininess) {

}

MaterialResource::MaterialResource(TextureResource *texture, float _shininess) : diffuseTextured(true), diffuseTexture(texture), shininess(_shininess) {

}

void MaterialResource::init() {
    // Material was created from an aiMaterial
    if (material.get() != nullptr) {
        aiColor3D _diffuse;
        if (material->Get(AI_MATKEY_COLOR_DIFFUSE, _diffuse) == AI_SUCCESS) {
            // Success
            diffuse.r = _diffuse.r;
            diffuse.g = _diffuse.g;
            diffuse.b = _diffuse.b;
        } else {
            // Failure
        }

        aiColor3D _specular;
        if (material->Get(AI_MATKEY_COLOR_SPECULAR, _specular) == AI_SUCCESS) {
            // Success
            specular.r = _specular.r;
            specular.g = _specular.g;
            specular.b = _specular.b;
        } else {
            // Failure
        }

        aiColor3D _ambient;
        if (material->Get(AI_MATKEY_COLOR_SPECULAR, _ambient) == AI_SUCCESS) {
            // Success
            ambient.r = _ambient.r;
            ambient.g = _ambient.g;
            ambient.b = _ambient.b;
        } else {
            // Failure
        }

        if (material->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS) {
            // Success
        } else {
            // Failure
        }
    }
}

void MaterialResource::pass(Shader *shader, std::string structName) {
    if (!diffuseTextured)
        (*shader)[structName + ".diffuse"] = diffuse;
    else {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseTexture->getTexture());
        (*shader)[structName + ".diffuse"] = 0;
    }

    (*shader)[structName + ".shininess"] = shininess;
}

} // namespace
