// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIRECT_H
#define SUNGUIRECT_H

#include <glm/glm.hpp>

#include <GL/glew.h>

class SunGUIRenderer;

class SunShader;

/// A rectangle in the GUI
class SunGUIRect {
friend SunGUIRenderer;
public:
    /// Constructs a rectangle from an origin point and size
    SunGUIRect(glm::ivec2 _origin, glm::ivec2 _size);

    /// Draws the rectangle with a specific color
    void draw(SunShader &shader, glm::mat4 projectionMatrix, glm::vec4 color) const;
private:
    static void createBuffers();

    /// The origin of the rectangle
    glm::ivec2 origin;

    /// The size of the rectangle
    glm::ivec2 size;

    /// The vertex data
    const static GLint vertices[];

    /// The index data
    const static GLuint indices[];

    /// The VBO, EBO, and VAO of the rectangle
    static GLuint VBO, EBO, VAO;

    /// A flag indicating that the necessary data has been loaded into OpenGL
    static bool GLinitialized;
};

#endif
