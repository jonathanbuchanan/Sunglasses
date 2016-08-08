// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/SunGUI.h>

#include <sunglasses/GUI/SunGUIView.h>
#include <sunglasses/GUI/SunGUIViewController.h>

namespace sunglasses {

SunGUI::SunGUI(SunGUIView *view, SunGUIWindow &_window) :
    window(_window), renderer(window), contentView(view) {

}

SunGUI::SunGUI(SunGUIViewController &viewController, SunGUIWindow &_window) :
    window(_window), renderer(window), contentView(&viewController.view) {

}

void SunGUI::update() {
    // Update the size of the viewport to match the framebuffer
    window.updateViewport();

    // Force the size of the content view to equal the window size
    contentView->size = window.size();

    // Update the GUI
    contentView->updateTree(glm::ivec2(0), window.updateInfo());
}

void SunGUI::draw() {
    // Clear the window
    window.clear();

    // Draw the GUI
    contentView->drawTree(glm::ivec2(0), renderer);

    // Swap the window's buffers
    window.swapBuffers();
}

} // namespace
