// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNMESH_H
#define SUNMESH_H

#include "SunShader.h"
#include "../Core/SunBase.h"

class SunObject;

class SunMeshResource;
class SunMaterialResource;

/// A class that represents a 3D object to be rendered
/**
 * The SunMesh class contains possible pointers to mesh resources (mesh data),
 * material resources, and texture resources. A SunObject contains a vector of these
 * and renders them every frame when the 'render' action is received.
 */
class SunMesh {
public:
    /// Constructs the mesh with a pointer to the owining object, mesh resource, and material resource
    SunMesh(SunObject *_object, SunMeshResource *_mesh, SunMaterialResource *_material);

    /// Renders the mesh
    /**
     * This method renders the mesh. The position and rotation vectors are added to
     * are added to the position and rotation of the owner (SunObject) to obtain
     * the global values.
     * @param shader A pointer to the shader to be used.
     */
    void render(SunShader *shader);
private:
    /// The pointer to the object that owns it
    SunObject *object;

    /// The pointer to the mesh resource that will be used for data
    SunMeshResource *mesh;

    /// The pointer to the material resource
    SunMaterialResource *material;
};

#endif
