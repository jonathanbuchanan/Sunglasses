// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <vector>

#include <glm/glm.hpp>

#include <GL/glew.h>

#include <sunglasses/Graphics/Texture.h>
#include <sunglasses/Graphics/Shader.h>
#include <sunglasses/Graphics/GeometryBuffer.h>
#include <sunglasses/Graphics/Window.h>
#include <sunglasses/GUI/Font.h>

#include <sunglasses/Graphics/2D/ColoredRectangle.h>
#include <sunglasses/Graphics/2D/TexturedRectangle.h>

namespace sunglasses {
namespace graphics {

/// A class used to store shaders for drawing the GUI
class Renderer2D {
public:
    /// Initializes the shaders
    Renderer2D(sunglasses::graphics::Window &_window);

    /// Draws all of the items in the tree
    void draw();
    
    /// Draws a rectangle with a solid color
    //void draw(glm::ivec2 position, glm::ivec2 size, glm::vec4 color);

    /// Draws a rectangle with a texture
    //void draw(glm::ivec2 position, glm::ivec2 size, glm::ivec2 textureSize, const graphics::Texture &texture);

    /// Draws text
    //void draw(glm::ivec2 position, std::string text, glm::vec4 color, Font &font);
private:
    /// Draws a colored rectangle
    void drawItem(const ColoredRectangle &rectangle);

    /// Draws a textured rectangle
    void drawItem(const TexturedRectangle &rectangle);

    /// A reference to the window
    sunglasses::graphics::Window &window;

    /// The fill shader
    sunglasses::graphics::Shader fillShader;

    /// The texture shader
    sunglasses::graphics::Shader textureShader;

    /// The text shader
    sunglasses::graphics::Shader textShader;

    /// The rectangle data used to draw rectangles
    graphics::GeometryBuffer<WIP::Vertex2D> rectangle = {{
        {{0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.0f, 1.0f}, {0.0f, 1.0f}},
        {{1.0f, 0.0f}, {1.0f, 0.0f}},
        {{1.0f, 1.0f}, {1.0f, 1.0f}}
    }, {0, 1, 2, 1, 2, 3}};
};

} // namespace
} // namespace

#endif
