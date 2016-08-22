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

/// A rectangle that is a component of every view
class Drawable {
public:
    /// Creates a copy of the object and returns a pointer (for polymorphism purposes)
    virtual Drawable * copy() const = 0;

    /// Draws the drawable using the renderer passed to it
    virtual void draw(glm::ivec2 position, glm::ivec2 size, Renderer2D &renderer) = 0;
};

/// A drawable of a single color
class DrawableSolidColor : public Drawable {
public:
    /// Constructs the drawable with a color
    DrawableSolidColor(glm::vec4 _color);

    /// Creates a copy of the object and return a pointer
    virtual Drawable * copy() const;

    /// Draws the rectangle with a solid color
    virtual void draw(glm::ivec2 position, glm::ivec2 size, Renderer2D &renderer);
private:
    /// The color of the drawable
    glm::vec4 color;
};

/// A drawable of a single image
class DrawableImage : public Drawable {
public:
    /// Constructs the drawable with a texture reference
    DrawableImage(Texture &_texture);

    /// Creates a copy of the object and returns a pointer
    virtual Drawable * copy() const;

    /// Draws the rectangle as an image
    virtual void draw(glm::ivec2 position, glm::ivec2 size, Renderer2D &renderer);
private:
    /// A reference to the texture
    Texture &texture;
};

} // namespace
} // namespace

#endif
