// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <vector>

#include <glm/glm.hpp>

#include <GL/glew.h>

#include <sunglasses/Graphics/Texture.h>
#include <sunglasses/Graphics/Shader.h>
#include <sunglasses/GUI/Drawable.h>

namespace sunglasses {
namespace GUI {

class Window;

/// A class used to store shaders for drawing the GUI
class Renderer2D {
public:
    /// Initializes the shaders
    Renderer2D(Window &_window);

    /// Draws a rectangle with a solid color
    void draw(glm::ivec2 position, glm::ivec2 size, glm::vec4 color);

    /// Draws a rectangle with a texture
    void draw(glm::ivec2 position, glm::ivec2 size, Texture &texture);
private:
    /// The window
    Window &window;

    /// The fill shader
    sunglasses::Shader fillShader;
    
    /// The texture shader
    sunglasses::Shader textureShader;

    /// The rectangle data used to draw rectangles
    struct Rectangle {
        /// Creates the OpenGL buffers
        Rectangle();

        /// The vertex data
        const GLfloat vertices[16] = {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f
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
} // namespace

#endif
