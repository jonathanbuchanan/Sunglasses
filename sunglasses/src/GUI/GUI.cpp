// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/GUI.h>

#include <sunglasses/GUI/View.h>
#include <sunglasses/GUI/ViewController.h>

namespace sunglasses {
namespace GUI {

GUI::GUI(View *view, Window &_window) :
    window(_window), renderer(window), contentView(view) {

}

GUI::GUI(ViewController &viewController, Window &_window) :
    window(_window), renderer(window), contentView(&viewController.view) {

}

void GUI::update() {
    // Update the size of the viewport to match the framebuffer
    window.updateViewport();

    // Force the size of the content view to equal the window size
    contentView->size = window.size();

    // Update the GUI
    contentView->updateTree(glm::ivec2(0), window.updateInfo());
}

void GUI::draw() {
    // Clear the window
    window.clear();

    // Draw the GUI
    contentView->drawTree(glm::ivec2(0), renderer);

    // Swap the window's buffers
    window.swapBuffers();
}

} // namespace
} // namespace
