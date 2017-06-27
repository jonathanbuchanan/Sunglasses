// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef CONTROL_H
#define CONTROL_H

#include <glm/glm.hpp>

#include <sunglasses/Core/Node.h>
#include <sunglasses/Core/Signal.h>

#include <vector>

namespace sunglasses {
namespace GUI {

class Renderer2D;

/// The abstract base class for GUI controls
class Control : public Node<Control> {
public:
    /// Constructs the control with a position, size, and its visibility
    Control(glm::ivec2 _position, glm::ivec2 _size, bool _visible = true);

    /// An enum representing the different possible states of the control
    enum struct State {
        Normal,
        Highlighted,
        Selected
    };

    /// Prepares the control to be hidden from view
    virtual void close();


    /// Called when the mouse moves
    void mouseMoved(glm::ivec2 offset, glm::ivec2 mouse);

    /// Called when the left mouse button is pressed
    void mouseLeftPressed(glm::ivec2 offset, glm::ivec2 mouse);

    /// Called when the left mouse button is released
    void mouseLeftReleased(glm::ivec2 offset, glm::ivec2 mouse);


    /// The signal emitted when the control is highlighted
    Signal<void()> signal_highlighted;

    /// The signal emitted when the control is selected
    Signal<void()> signal_selected;

    /// The signal emitted when the control is unhighlighted
    Signal<void()> signal_unhighlighted;

    /// The signal emitted when the control is deselected
    Signal<void()> signal_deselected;

    /// Checks a point to see if the control contains it
    bool contains(glm::ivec2 offset, glm::ivec2 point);


    /// The position of the control
    glm::ivec2 position;

    /// The size of the control
    glm::ivec2 size;

    /// The visibility of the control
    /**
     * Controls the visibility of the control. Any children of a non-visible
     * control are also not drawn.
     */
    bool visible;
protected:
    /// Draws the control
    /**
     * @param offset The position offset of the control (globally)
     * @param renderer A reference to the renderer
     */
    virtual void draw(glm::ivec2 offset, Renderer2D &renderer) = 0;

    /// The state of the control
    State state;
private:
    /// Highlights the control
    void highlight();

    /// Unhighlights the control
    void unhighlight();

    /// Selects the control
    void select();

    /// Unselects the control
    /**
     * Unselects the control and returns it to the specified state.
     */
    void unselect(State next);
};

} // namespace
} // namespace

#endif
