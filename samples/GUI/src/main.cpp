// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Sunglasses.hpp>

#include "GUIMainMenu.h"

int main(int argc, char **argv) {
    SunGUIWindow window = SunGUIWindow(640, 480, "GUI Demo");

    GUIMainMenu mainMenu(window);

    SunGUI gui = SunGUI(mainMenu, window);

    while (true) {
        gui.update();
        gui.draw();
    }

    return 0;
}
