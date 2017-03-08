// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Sunglasses.hpp>

using namespace sunglasses;


#include "MainMenu.h"

int main(int argc, char **argv) {
    bool running = true;

    graphics::Window window(glm::ivec2(1920, 1080), "Voxel");

    LSlot<void()> slot_close([&running]() { running = false; });

    connect(window.signal_close, slot_close);

    GUI::System GUI(window);

    MainMenu main(GUI);

    while (running) {
        window.update();
        GUI.draw();
    }

    return 0;
}
