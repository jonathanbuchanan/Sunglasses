// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef COMPONENT_H
#define COMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace sunglasses {

/// A component that represents a transformation in 3D space
struct Transform {
    /// The position in space as a vector
    glm::vec3 position;

    /// The orientation as a quaternion
    glm::quat orientation;
};

/// A component that represents a transformation in 2D space
struct Transform2 {

};

} // sunglasses

#endif
