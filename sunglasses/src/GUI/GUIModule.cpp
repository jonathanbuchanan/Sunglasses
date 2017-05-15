// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/GUIModule.h>

#include <sunglasses/Graphics/GraphicsModule.h>

namespace sunglasses {
namespace GUI {

GUIModule::GUIModule(graphics::GraphicsModule &_graphicsModule) :
        graphicsModule(_graphicsModule), root(nullptr) {
    connect(graphicsModule.window.cursor.signal_move, slot_move);
    connect(graphicsModule.window.cursor.signal_pressLeft, slot_pressLeft);
    connect(graphicsModule.window.cursor.signal_releaseLeft, slot_releaseLeft);
    connect(graphicsModule.window.cursor.signal_pressMiddle, slot_pressMiddle);
    connect(graphicsModule.window.cursor.signal_releaseMiddle, slot_releaseMiddle);
    connect(graphicsModule.window.cursor.signal_pressRight, slot_pressRight);
    connect(graphicsModule.window.cursor.signal_releaseRight, slot_releaseRight);
}

void GUIModule::present(Control &control) {
    root = &control;
}

void GUIModule::update() {
    
}

void GUIModule::run() {
    
}

const graphics::GraphicsModule & GUIModule::getGraphicsModule() {
    return graphicsModule;
}

void GUIModule::mouse_move(glm::ivec2 location) {
    if (root != nullptr)
        root->mouseMoved(glm::ivec2(0), location);
}

void GUIModule::mouse_pressLeft(glm::ivec2 mouse) {
    if (root != nullptr)
        root->mouseLeftPressed(glm::ivec2(0), mouse);
}

void GUIModule::mouse_releaseLeft(glm::ivec2 mouse) {
    if (root != nullptr)
        root->mouseLeftReleased(glm::ivec2(0), mouse);
}

void GUIModule::mouse_pressMiddle(glm::ivec2 mouse) {

}

void GUIModule::mouse_releaseMiddle(glm::ivec2 mouse) {

}

void GUIModule::mouse_pressRight(glm::ivec2 mouse) {

}

void GUIModule::mouse_releaseRight(glm::ivec2 mouse) {

}

} // namespace
} // namespace
