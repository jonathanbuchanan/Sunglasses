// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNMESH_H
#define SUNMESH_H

#include <sunglasses/Graphics/SunShader.h>
#include <sunglasses/Core/SunBase.h>

class SunObject;

class SunMeshResource;
class SunMaterialResource;

#include <glm/glm.hpp>

/// A class that represents a 3D object to be rendered
/**
 * The SunMesh class contains possible pointers to mesh resources (mesh data),
 * material resources, and texture resources. A SunObject contains a vector of these
 * and renders them every frame when the 'render' action is received.
 */
class SunMesh {
    friend SunObject;
public:
    /// Constructor with no arguments
    SunMesh();

    /// Constructs the mesh with a pointer to the owning object, mesh resource, and material resource
    SunMesh(SunObject *_object, SunMeshResource *_mesh, SunMaterialResource *_material);

    /// Constructs the mesh with a pointer to the owning object, mesh resource, material resource, and some values
    SunMesh(SunObject *_object, SunMeshResource *_mesh, SunMaterialResource *_material, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);

    /// Renders the mesh
    /**
     * This method renders the mesh. The position and rotation vectors are added to
     * are added to the position and rotation of the owner (SunObject) to obtain
     * the global values.
     * @param shader A pointer to the shader to be used.
     */
    void render(SunShader *shader);

    /// Sets the position of the mesh
    void setPosition(glm::vec3 _position) { position = _position; }

    /// Sets the rotation of the mesh
    void setRotation(glm::vec3 _rotation) { rotation = _rotation; }

    /// Sets the scale of the mesh
    void setScale(glm::vec3 _scale) { scale = _scale; }
private:
    /// The pointer to the object that owns it
    SunObject *object;

    /// The pointer to the mesh resource that will be used for data
    SunMeshResource *mesh;

    /// The pointer to the material resource
    SunMaterialResource *material;

    /// The position of the mesh (relative to the object)
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

    /// The rotation of the mesh (relative to the object)
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    /// The scale of the mesh (relative to the object)
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

#endif
