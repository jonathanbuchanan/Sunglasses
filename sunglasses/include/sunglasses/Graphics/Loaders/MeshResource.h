// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef MESHRESOURCE_H
#define MESHRESOURCE_H

#include <sunglasses/Graphics/Primitives.h>
#include <sunglasses/Extern/Resource.h>

#include <memory>

struct aiMesh;

namespace sunglasses {

/// A Resource subclass representing loaded mesh data
/**
 * This class contains loaded mesh data, but no code for actually rendering. To
 * render, it is recommended to keep a reference to one of these and render it from
 * there. This resource is designed to be created by ModelResource, so its constructor
 * uses an Assimp mesh.
 */
class MeshResource : public Resource {
public:
    /// Constructs the resource from the mesh.
    MeshResource(aiMesh *_mesh);

    /// Initializes the mesh
    virtual void init();

    /// Gets the vertex buffer object
    GLuint getVBO() { return VBO; }

    /// Gets the vertex array object
    GLuint getVAO() { return VAO; }

    /// Gets the element buffer object
    GLuint getEBO() { return EBO; }

    /// Gets the number of indices
    int getIndicesSize() { return indices.size(); }

    /// Gets the vertex vector
    std::vector<Vertex> getVertices() { return vertices; }

    /// Gets the indices vector
    std::vector<GLuint> getIndices() { return indices; }
private:
    /// The vector containing the vertex data
    std::vector<Vertex> vertices;

    /// The vector containing the index data
    std::vector<GLuint> indices;

    /// The Vertex Buffer Object
    GLuint VBO;

    /// The Vertex Array Object
    GLuint VAO;

    /// The Element Buffer Object
    GLuint EBO;

    /// The aiMesh pointer
    aiMesh *mesh;
};

} // namespace

#endif
