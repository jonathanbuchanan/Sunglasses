// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNMATERIALRESOURCE_H
#define SUNMATERIALRESOURCE_H

#include "../../Extern/SunResource.h"

class SunObject;
class SunShader;
class SunTextureResource;

#include <glm/glm.hpp>

#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct aiMaterial;

/// A SunResource subclass representing loaded material data
class SunMaterialResource : public SunResource {
    friend SunObject;
public:
    /// Constructs the material from an aiMaterial.
    /**
     * @param _material A pointer to the aiMaterial
     */
    SunMaterialResource(aiMaterial *_material);

    /// Constructs the material from a single color and shininess.
    /**
     * This constructor builds the material resource from a single color, assigning
     * the diffuse, specular, and ambient colors with the same value and the shininess
     * value with a float.
     * @param color The color value
     * @param _shininess The shininess value
     */
    SunMaterialResource(glm::vec3 color, float _shininess);

    /// Constructs the material from a single texture and shininess.
    /**
     * This constructor builds the material resource from a single texture, assigning the diffuse,
     * specular, and ambient textures with the same pointer and the shininess value with a
     * float.
     * @param texture The pointer to the texture resource
     * @param _shininess The shininess value
     */
    SunMaterialResource(SunTextureResource *texture, float _shininess);

    /// Initializes the material
    /**
     * In the case of the material being generated from an aiMaterial, this
     * initializes the resource by copying all of the values. Otherwise, if
     * if the values were initialized by the constructor, this does nothing because
     * the values already are loaded.
     */
    void init();

    /// Passes the material as a uniform for a shader in a struct.
    /**
     * This member function passes the material as a struct in a shader.
     * @param shader The pointer to the shader
     * @param structName The name of the struct in the shader
     */
    void pass(SunShader *shader, std::string structName);

    /// Gets the diffuse color
    glm::vec3 getDiffuse() { return diffuse; }

    /// Gets the specular color
    glm::vec3 getSpecular() { return specular; }

    /// Gets the ambient color
    glm::vec3 getAmbient() { return ambient; }

    /// Gets the shininess value
    double getShininess() { return shininess; }
private:
    /// The aiMaterial pointer
    std::unique_ptr<aiMaterial> material;

    /// A boolean that states whether the material has diffuse set as a solid color or a texture
    bool diffuseTextured = false;

    /// The diffuse color of the material
    glm::vec3 diffuse;

    /// The diffuse texture of the material
    SunTextureResource *diffuseTexture;

    /// The specular color of the material
    glm::vec3 specular;

    /// The ambient color of the material
    glm::vec3 ambient;

    /// The shininess of the material
    /**
     * This value is the shininess of the material. This value is specifically
     * used as the exponent in the Phong equation.
     */
    double shininess;
};

#endif
