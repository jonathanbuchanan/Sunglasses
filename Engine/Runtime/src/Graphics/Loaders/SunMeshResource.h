// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNMESHRESOURCE_H
#define SUNMESHRESOURCE_H

#include "../SunPrimitives.h"
#include "../../Extern/SunResource.h"

#include <memory>

struct aiMesh;

/// A SunResource subclass representing loaded mesh data
/**
 * This class contains loaded mesh data, but no code for actually rendering. To
 * render, it is recommended to keep a reference to one of these and render it from
 * there. This resource is designed to be created by SunModelResource, so its constructor
 * uses an Assimp mesh.
 */
class SunMeshResource : public SunResource {
public:
    /// Constructs the resource from the mesh.
    SunMeshResource(aiMesh *_mesh);

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
private:
    /// The vector containing the vertex data
    std::vector<SunVertex> vertices;

    /// The vector containing the index data
    std::vector<GLuint> indices;

    /// The Vertex Buffer Object
    GLuint VBO;

    /// The Vertex Array Object
    GLuint VAO;

    /// The Element Buffer Object
    GLuint EBO;

    /// The aiMesh pointer
    std::unique_ptr<aiMesh> mesh;
};

#endif
