#ifndef SUNMATERIALRESOURCE_H
#define SUNMATERIALRESOURCE_H

#include "../../Extern/SunResource.h"

#include <glm/glm.hpp>

#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class aiMaterial;

/// A SunResource subclass representing loaded material data
class SunMaterialResource : public SunResource {
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

    /// Initializes the material
    /**
     * In the case of the material being generated from an aiMaterial, this
     * initializes the resource by copying all of the values. Otherwise, if
     * if the values were initialized by the constructor, this does nothing because
     * the values already are loaded.
     */
    void init();

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

    /// The diffuse color of the material
    glm::vec3 diffuse;

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
