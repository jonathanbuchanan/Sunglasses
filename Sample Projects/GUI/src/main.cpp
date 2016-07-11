// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Sunglasses.hpp>

#include "GUIMainMenu.h"

int main(int argc, char **argv) {
    SunGUIWindow window = SunGUIWindow(640, 480, "GUI Demo");

    GUIMainMenu mainMenu = GUIMainMenu(window);

    SunGUI gui = SunGUI(mainMenu, window);

    return 0;
}
