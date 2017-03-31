// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef PANEL_H
#define PANEL_H

#include <glm/glm.hpp>

#include <sunglasses/GUI/Control.h>
#include <sunglasses/GUI/Drawable.h>
#include <sunglasses/Graphics/Window.h>

#include <vector>
#include <memory>

namespace sunglasses {
namespace GUI {

class ViewController;
class Renderer2D;

/// The state of a control
enum class ControlState {
    Normal,
    Highlighted,
    Selected
};

/// A panel in the GUI toolkit
/**
 * A panel is a single object that displays a single drawable.
 * This is useful for displaying non-interactive images, but
 * also it is used as the root for displaying the GUI system.
 */
template<typename T>
class Panel : public Control {
public:
    /// Constructs the panel
    Panel(glm::ivec2 _position, glm::ivec2 _size, const T &_background,
            bool _visible = true, std::initializer_list<Control *> children = {}) :
            Control(_position, _size, _visible, children), background(_background) {

    }

    /// Constructs the panel within the frame of the window
    Panel(const graphics::Window &window, const T &_background, bool _visible = true,
            std::initializer_list<Control *> children = {}) :
            Control(glm::ivec2(0, 0), window.getSize(), _visible, children),
            background(_background) {

    }

    /// The background (must be a drawable)
    T background;
protected:
    /// Draws the panel
    /**
     * This method draws the drawable sized over
     * the entire panel.
     */
    virtual void draw(glm::ivec2 offset, Renderer2D &renderer) {
        glm::ivec2 absolute = offset + position;
        background.draw(absolute, size, renderer);
    }
};

/// A 'basic' panel
/**
 * A 'basic' panel, which consists of a simple
 * single-color only background.
 */
using BasicPanel = Panel<Drawable::Color>;

/// An 'image' panel
/**
 * An 'image' panel, which consists of an image
 * background.
 */
using ImagePanel = Panel<Drawable::Image>;

} // namespace
} // namespace

#endif
