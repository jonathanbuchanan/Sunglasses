// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GUIMODULE_H
#define GUIMODULE_H

#include <functional>

#include <sunglasses/Core/Program.h>
#include <sunglasses/GUI/Control.h>
#include <sunglasses/Graphics/2D/Renderer2D.h>

namespace sunglasses {
namespace graphics {

class GraphicsModule;

}

namespace GUI {

/// A GUI containing a window and a content view
class GUIModule : public Module {
public:
    /// Constructs the GUI
    GUIModule(graphics::GraphicsModule &_graphicsModule);

    /// Changes the root control
    void present(Control &control);

    /// Updates the GUI
    virtual void update();

    /// Runs the GUI (does nothing)
    virtual void run();

    /// Returns a reference to the graphics module
    const graphics::GraphicsModule & getGraphicsModule();
    
    /// Returns a reference to the renderer
    const graphics::Renderer2D & getRenderer();
private:
    /// Called when the mouse moves
    void mouse_move(glm::ivec2 location);
    Slot<void(GUIModule::*)(glm::ivec2), &GUIModule::mouse_move> slot_move = {*this};

    /// Called when the left mouse button is pressed
    void mouse_pressLeft(glm::ivec2 mouse);
    Slot<void(GUIModule::*)(glm::ivec2), &GUIModule::mouse_pressLeft> slot_pressLeft = {*this};

    /// Called when the left mouse button is released
    void mouse_releaseLeft(glm::ivec2 mouse);
    Slot<void(GUIModule::*)(glm::ivec2), &GUIModule::mouse_releaseLeft> slot_releaseLeft = {*this};

    /// Called when the middle mouse button is pressed
    void mouse_pressMiddle(glm::ivec2 mouse);
    Slot<void(GUIModule::*)(glm::ivec2), &GUIModule::mouse_pressMiddle> slot_pressMiddle = {*this};

    /// Called when the middle mouse button is released
    void mouse_releaseMiddle(glm::ivec2 mouse);
    Slot<void(GUIModule::*)(glm::ivec2), &GUIModule::mouse_releaseMiddle> slot_releaseMiddle = {*this};

    /// Called when the right mouse button is pressed
    void mouse_pressRight(glm::ivec2 mouse);
    Slot<void(GUIModule::*)(glm::ivec2), &GUIModule::mouse_pressRight> slot_pressRight = {*this};

    /// Called when the right mouse button is released
    void mouse_releaseRight(glm::ivec2 mouse);
    Slot<void(GUIModule::*)(glm::ivec2), &GUIModule::mouse_releaseRight> slot_releaseRight = {*this};

    /// A reference to the graphics module
    graphics::GraphicsModule &graphicsModule;
    
    /// The 2D renderer
    graphics::Renderer2D renderer;
    
    /// The root control
    Control *root;
};

} // namespace
} // namespace

#endif
