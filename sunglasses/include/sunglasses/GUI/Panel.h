// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef PANEL_H
#define PANEL_H

#include <glm/glm.hpp>

#include <sunglasses/GUI/Control.h>
#include <sunglasses/GUI/Window.h>
#include <sunglasses/GUI/Drawable.h>

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
class Panel : public Control {
friend ViewController;
public:
    /// Constructs the panel
    Panel(glm::ivec2 _position, glm::ivec2 _size,
        const Drawable &_drawable, bool _visible = true);

    /// Draws the panel
    /**
     * This method draws the drawable sized over
     * the entire panel.
     */
    virtual void draw(glm::ivec2 offset, Renderer2D &renderer);
protected:
    /// The drawable (a solid color, image, etc.)
    std::unique_ptr<Drawable> drawable;

    /// The visibility of the view
    bool visible;
};

} // namespace
} // namespace

#endif
