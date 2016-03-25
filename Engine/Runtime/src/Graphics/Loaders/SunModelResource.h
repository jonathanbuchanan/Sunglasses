// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNMODELRESOURCE_H
#define SUNMODELRESOURCE_H

#include "../../Extern/SunResource.h"

#include <vector>
#include <string>
#include <map>
#include <memory>

#include <assimp/Importer.hpp>

class aiScene;

/// An SunResource subclass for loading 3D model files
/**
 * This subclass of SunResource is made to contain 3D model data. It has code to load
 * mesh data from a file using Assimp.
 * It provides access to its OpenGL buffers so that it can be used by meshes,
 * or it can be copied for a more direct manipulation of it.
 */
class SunModelResource : public SunResource {
public:
    /// Constructor that initializes the path
    SunModelResource(std::string _path);

    /// Constructor that initializes the path and the mesh map
    SunModelResource(std::string _path, std::map<std::string, SunResource *> *_meshMap);

    /// Initializes the resource
    /**
     * This method is called when the resource is added to the resource manager.
     */
    virtual void init();
private:
    /// The path to the 3D model file
    std::string path;

    /// The pointer to the mesh map
    std::map<std::string, SunResource *> *meshMap;

    /// The Assimp importer
    Assimp::Importer importer;

    /// The pointer to the scene
    const aiScene *scene;
};

#endif
