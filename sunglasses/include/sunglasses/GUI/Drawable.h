// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>

#include <sunglasses/Graphics/Texture.h>
#include <sunglasses/GUI/Font.h>

namespace sunglasses {

namespace GUI {

class Renderer2D;

namespace Drawable {

/// A drawable of a single color
class Color {
public:
    /// Constructs the drawable with a color
    Color(glm::vec4 _color);

    /// Assigns a color
    Color & operator=(glm::vec4 _color);

    /// Draws the rectangle with a solid color
    void draw(glm::ivec2 position, glm::ivec2 size, Renderer2D &renderer);
private:
    /// The color
    glm::vec4 color;
};

/// A drawable of a single image
class Image {
public:
    /// Constructs the drawable with a texture reference
    Image(const graphics::Texture &_texture);

    /// Draws the rectangle as an image
    void draw(glm::ivec2 position, glm::ivec2 size, Renderer2D &renderer);
private:
    /// A reference to the texture
    const graphics::Texture &texture;
};

/// A drawable string of text
class Text {
public:
    /// Constructs the drawable with a string, color, and font
    Text(std::string _text, glm::vec4 _color, Font &_font);

    /// Draws the text at the given position
    void draw(glm::ivec2 position, Renderer2D &renderer);
private:
    /// The string of text to draw
    std::string text;

    /// The color of the text to draw
    glm::vec4 color;

    /// The font to be used
    Font &font;
};

} // namespace
} // namespace
} // namespace

#endif
