// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <glm/glm.hpp>

#include <GL/glew.h>

#include <sunglasses/Graphics/Shader.h>
#include <sunglasses/GUI/Drawable.h>

namespace sunglasses {

class Window;

/// A container used to store shaders for drawing the GUI
class Renderer {
public:
    /// Initializes the shaders
    Renderer(Window &_window);

    /// Renders a rectangle
    void drawRect(glm::ivec2 origin, glm::ivec2 size, Drawable *drawable);
private:
    /// The window
    Window &window;

    /// The fill shader
    Shader fillShader;

    /// The rectangle data used to draw rectangles
    struct Rectangle {
        /// Creates the OpenGL buffers
        Rectangle();

        /// The vertex data
        const GLint vertices[8] = {
            0, 0,
            0, 1,
            1, 0,
            1, 1
        };

        /// The index data
        const GLuint indices[6] = {
            0, 1, 2,
            1, 2, 3
        };

        /// The VBO, EBO, and VAO
        GLuint VBO, EBO, VAO;
    } rectangle;
};

} // namespace

#endif
