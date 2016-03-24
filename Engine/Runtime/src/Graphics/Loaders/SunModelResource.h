// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNMODELRESOURCE_H
#define SUNMODELRESOURCE_H

#include "../../Extern/SunResource.h"

/// An abstract SunResource subclass for loading .dae (collada) files
/**
 * This subclass of SunResource is made to contain 3D model data. There is not
 * code for loading the data from disk, that must be provided in subclasses.
 * It provides access to its OpenGL buffers so that it can be used by meshes,
 * or it can be copied for a more direct manipulation of it.
 */
class SunModelResource : public SunResource {
public:

private:

};

#endif
