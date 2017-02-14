// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Sunglasses.hpp>

#include "GUIMainMenu.h"

using namespace sunglasses;

int main(int argc, char **argv) {
    bool running = true;

    GUI::Font::LibraryT fonts({
        {"arial", GUI::Font::LibraryT::ResourceHandle(GUI::Font::Parameter("/usr/share/fonts/TTF/Hack-Regular.ttf", glm::vec2(12, 12), glm::ivec2(220, 220)))}
    });

    Font &arial = fonts.at("arial");

    graphics::Window window = graphics::Window(glm::ivec2(640, 480), "GUI Demo");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    LSlot<void()> slot_close = LSlot<void()>([&running]() { running = false; });

    connect(window.signal_close, slot_close);

    GUI::System gui(window);

    GUIMainMenu mainMenu(gui, fonts);

    while (running) {
        window.update();
        gui.draw();
    }

    return 0;
}
