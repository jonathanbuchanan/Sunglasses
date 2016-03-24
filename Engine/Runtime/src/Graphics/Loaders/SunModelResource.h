// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNMODELRESOURCE_H
#define SUNMODELRESOURCE_H

#include "../SunPrimitives.h"
#include "../../Extern/SunResource.h"

#include <vector>
#include <string>
#include <map>
#include <memory>

/// A struct representing loaded mesh data
/**
 * This struct contains loaded mesh data, but no code for actually rendering. To
 * render, it is recommended to keep a reference to one of these and render it from
 * there.
 */
struct SunMeshData {
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
};

/// An abstract SunResource subclass for loading .dae (collada) files
/**
 * This subclass of SunResource is made to contain 3D model data. There is not
 * code for loading the data from disk, that must be provided in subclasses.
 * It provides access to its OpenGL buffers so that it can be used by meshes,
 * or it can be copied for a more direct manipulation of it.
 */
class SunModelResource : public SunResource {
public:
    /// Loads the meshes
    /**
     * This pure virtual method should be overridden in every subclass and should
     * load the mesh data from a file. In that process, it should call addMesh()
     * for each mesh loaded.
     */
    virtual void processMeshes() = 0;

    /// Initializes the resource
    /**
     * This method is called when the resource is added to the resource manager,
     * and calls processMeshes(), which should be overridden to load the mesh data.
     */
    virtual void init();
protected:
    /// Loads a SunMeshData into the OpenGL context
    /**
     * This member function adds the given SunMeshData pointer to the map for the
     * name. This also initializes it by generating the VBO, VAO, and EBO. This should
     * be the last thing done while loading a single mesh.
     * @param name The name of the mesh
     * @param mesh The pointer to the mesh
     */
    void addMesh(std::string name, SunMeshData *mesh);
private:
    /// The map of mesh pointers with strings as keys
    std::map<std::string, std::unique_ptr<SunMeshData>> meshes;
};

#endif
