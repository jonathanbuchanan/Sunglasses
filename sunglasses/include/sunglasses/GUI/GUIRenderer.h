// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GUIRENDERER_H
#define GUIRENDERER_H

#include <vector>

#include <glm/glm.hpp>

#include <GL/glew.h>

#include <sunglasses/Graphics/Shader.h>
#include <sunglasses/GUI/GUIDrawable.h>

namespace sunglasses {

class GUIWindow;

/// A container used to store shaders for drawing the GUI
class GUIRenderer {
public:
    /// Initializes the shaders
    GUIRenderer(GUIWindow &_window);

    /// Renders a rectangle
    void drawRect(glm::ivec2 origin, glm::ivec2 size, GUIDrawable *drawable);
private:
    /// The window
    GUIWindow &window;

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
