// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <sunglasses/Graphics/Texture.h>

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
    Image(Texture &_texture);

    /// Draws the rectangle as an image
    void draw(glm::ivec2 position, glm::ivec2 size, Renderer2D &renderer);
private:
    /// A reference to the texture
    Texture &texture;
};

} // namespace
} // namespace
} // namespace

#endif
