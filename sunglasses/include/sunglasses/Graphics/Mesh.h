// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef MESH_H
#define MESH_H

#include <sunglasses/Graphics/Shader.h>
#include <sunglasses/Core/Base.h>

#include <glm/glm.hpp>

namespace sunglasses {

class Object;
class MeshResource;
class MaterialResource;

namespace graphics {


/// A class that represents a 3D object to be rendered
/**
 * The Mesh class contains possible pointers to mesh resources (mesh data),
 * material resources, and texture resources. A Object contains a vector of these
 * and renders them every frame when the 'render' action is received.
 */
class Mesh {
    friend Object;
public:
    /// Constructor with no arguments
    Mesh();

    /// Constructs the mesh with a pointer to the owning object, mesh resource, and material resource
    Mesh(Object *_object, MeshResource *_mesh, MaterialResource *_material);

    /// Constructs the mesh with a pointer to the owning object, mesh resource, material resource, and some values
    Mesh(Object *_object, MeshResource *_mesh, MaterialResource *_material, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);

    /// Renders the mesh
    /**
     * This method renders the mesh. The position and rotation vectors are added to
     * are added to the position and rotation of the owner (Object) to obtain
     * the global values.
     * @param shader A pointer to the shader to be used.
     */
    void render(Shader *shader);

    /// Sets the position of the mesh
    void setPosition(glm::vec3 _position) { position = _position; }

    /// Sets the rotation of the mesh
    void setRotation(glm::vec3 _rotation) { rotation = _rotation; }

    /// Sets the scale of the mesh
    void setScale(glm::vec3 _scale) { scale = _scale; }
private:
    /// The pointer to the object that owns it
    Object *object;

    /// The pointer to the mesh resource that will be used for data
    MeshResource *mesh;

    /// The pointer to the material resource
    MaterialResource *material;

    /// The position of the mesh (relative to the object)
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

    /// The rotation of the mesh (relative to the object)
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    /// The scale of the mesh (relative to the object)
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

} // namespace
} // namespace

#endif
