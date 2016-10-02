// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef BUTTON_H
#define BUTTON_H

#include <sunglasses/GUI/Panel.h>
#include <sunglasses/GUI/Drawable.h>
#include <sunglasses/GUI/Renderer2D.h>
#include <sunglasses/GUI/Signal.h>

#include <functional>
#include <vector>

namespace sunglasses {
namespace GUI {

/// A button in the GUI
template<typename T, typename S, typename R>
class Button : public Control {
public:
    /// Constructs the button with three different backgrounds
    Button(glm::ivec2 _position, glm::ivec2 _size, const T &_normalBackground,
            const S &_highlightedBackground, const R &_selectedBackground) :
            Control(_position, _size), normalBackground(_normalBackground),
            highlightedBackground(_highlightedBackground), selectedBackground(_selectedBackground) {

    }

    /// The background for the 'normal' state
    T normalBackground;

    /// The background for the 'highlighted' state
    S highlightedBackground;

    /// The background for the 'selected' state
    R selectedBackground;
protected:
    /// Draws the button
    virtual void draw(glm::ivec2 offset, Renderer2D &renderer) {
        switch (state) {
        case State::Normal:
            normalBackground.draw(offset + position, size, renderer);
            break;
        case State::Highlighted:
            highlightedBackground.draw(offset + position, size, renderer);
            break;
        case State::Selected:
            selectedBackground.draw(offset + position, size, renderer);
            break;
        }
    }
private:
};

/// A 'basic' button
using BasicButton = Button<Drawable::Color, Drawable::Color, Drawable::Color>;

} // namespace
} // namespace

#endif
