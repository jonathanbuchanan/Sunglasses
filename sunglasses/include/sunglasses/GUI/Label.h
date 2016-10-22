// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef LABEL_H
#define LABEL_H

#include <sunglasses/GUI/Control.h>
#include <sunglasses/GUI/Drawable.h>
#include <sunglasses/GUI/Renderer2D.h>

#include <string>

namespace sunglasses {
namespace GUI {

/// A label in the GUI toolkit
class Label : public Control {
public:
    /// Constructs the label with a size, position, and text drawable
    Label(glm::ivec2 _size, glm::ivec2 _position, const Drawable::Text &_text);

    /// The text drawable
    Drawable::Text text;
protected:
    /// Draws the label
    virtual void draw(glm::ivec2 offset, Renderer2D &renderer);
private:

};

} // namespace
} // namespace

#endif
