// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIRENDERING_H
#define SUNGUIRENDERING_H

#include <vector>

#include <glm/glm.hpp>

#include <GL/gl.h>

/// An object that contains vertex data that can be filled
class SunGUIFill {
public:
    /// Constructs an object from a set of vertices
    SunGUIFill(const std::vector<glm::ivec2> &vertices);
private:
    /// The VBO and VAO
    GLuint VBO, VAO;
};

#endif
