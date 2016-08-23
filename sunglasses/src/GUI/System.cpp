// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/System.h>

#include <sunglasses/GUI/Panel.h>
#include <sunglasses/GUI/Controller.h>

namespace sunglasses {
namespace GUI {

System::System(Panel *panel, Window &_window) :
    window(_window), renderer(window), content(panel) {

}

System::System(Controller &viewController, Window &_window) :
    window(_window), renderer(window), content(&viewController.view) {

}

void System::update() {
    // Update the size of the viewport to match the framebuffer
    window.updateViewport();

    // Force the size of the content view to equal the window size
    content->size = window.size();

    // Update the GUI
    content->update(glm::ivec2(0), window.updateInfo());
    content->updateChildren(glm::ivec2(0), window.updateInfo());
}

void System::draw() {
    // Clear the window
    window.clear();

    // Draw the GUI
    content->draw(glm::ivec2(0), renderer);
    content->drawChildren(glm::ivec2(0), renderer);

    // Swap the window's buffers
    window.swapBuffers();
}

} // namespace
} // namespace
