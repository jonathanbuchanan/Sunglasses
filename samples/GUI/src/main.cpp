// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Sunglasses.hpp>

#include "GUIMainMenu.h"

using namespace sunglasses;

int main(int argc, char **argv) {
    GUI::Window window = GUI::Window(640, 480, "GUI Demo");

    GUIMainMenu mainMenu(window);

    GUI::System gui = GUI::System(mainMenu, window);

    while (true) {
        gui.update();
        gui.draw();
    }

    return 0;
}
