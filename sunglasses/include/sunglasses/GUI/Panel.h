// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef PANEL_H
#define PANEL_H

#include <glm/glm.hpp>

#include <sunglasses/GUI/Control.h>
#include <sunglasses/Graphics/Window.h>
#include <sunglasses/Graphics/2D/ColoredRectangle.h>

namespace sunglasses {
namespace GUI {

/// A panel in the GUI toolkit
/**
 * A panel is a control that displays a single-colored rectangle.
 */
class Panel : public Control {
public:
    /// Constructs the panel
    Panel(glm::ivec2 _position, glm::ivec2 _size,
    	graphics::ColoredRectangle::Color _background = glm::vec4(1.0f), bool _visible = true);

    /// Constructs the panel within the frame of the window
    Panel(const graphics::Window &window, graphics::ColoredRectangle::Color _background = glm::vec4(1.0f),
    	bool _visible = true);

    /// The background (must be a drawable)
    graphics::ColoredRectangle background;
};

} // namespace
} // namespace

#endif
