// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIRENDERER_H
#define SUNGUIRENDERER_H

#include <vector>

#include <glm/glm.hpp>

#include <GL/glew.h>

#include <sunglasses/Graphics/SunShader.h>
#include <sunglasses/GUI/SunGUIDrawable.h>

class SunGUIWindow;

/// A container used to store shaders for drawing the GUI
class SunGUIRenderer {
public:
    /// Initializes the shaders
    SunGUIRenderer(SunGUIWindow &_window);

    /// Renders a rectangle
    void drawRect(glm::ivec2 origin, glm::ivec2 size, SunGUIDrawable *drawable);
private:
    /// The window
    SunGUIWindow &window;

    /// The fill shader
    SunShader fillShader;

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

#endif
