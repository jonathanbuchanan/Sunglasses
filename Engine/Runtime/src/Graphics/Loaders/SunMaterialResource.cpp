#include "SunMaterialResource.h"

SunMaterialResource::SunMaterialResource(aiMaterial *_material) : material(_material) {

}

SunMaterialResource::SunMaterialResource(glm::vec3 color, float _shininess) : material(nullptr), diffuse(color), specular(color), ambient(color), shininess(_shininess) {

}

void SunMaterialResource::init() {
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
