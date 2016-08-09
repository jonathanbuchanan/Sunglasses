// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef MODELRESOURCE_H
#define MODELRESOURCE_H

#include <sunglasses/Extern/Resource.h>

#include <vector>
#include <string>
#include <map>
#include <memory>

#include <assimp/Importer.hpp>

struct aiScene;

namespace sunglasses {

/// An Resource subclass for loading 3D model files
/**
 * This subclass of Resource is made to contain 3D model data. It has code to load
 * mesh data from a file using Assimp.
 * It provides access to its OpenGL buffers so that it can be used by meshes,
 * or it can be copied for a more direct manipulation of it.
 */
class ModelResource : public Resource {
public:
    /// Constructor that initializes the path
    ModelResource(std::string _path);

    /// Constructor that initializes the path and the mesh map
    ModelResource(std::string _path, std::map<std::string, Resource *> *_meshMap);

    /// Constructor that initializes the path, mesh map, and material map
    ModelResource(std::string _path, std::map<std::string, Resource *> *_meshMap, std::map<std::string, Resource *> *_materialMap);

    /// Initializes the resource
    /**
     * This method is called when the resource is added to the resource manager.
     */
    virtual void init();
private:
    /// The path to the 3D model file
    std::string path;

    /// The pointer to the mesh map
    std::map<std::string, Resource *> *meshMap;

    /// The pointer to the material map
    std::map<std::string, Resource *> *materialMap;

    /// The Assimp importer
    Assimp::Importer importer;

    /// The pointer to the scene
    const aiScene *scene;
};

} // namespace

#endif
