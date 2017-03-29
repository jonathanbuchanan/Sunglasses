// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Sunglasses.hpp>

#include "GUIMainMenu.h"

using namespace sunglasses;

class GUIProgram : public Program {
public:
    GUIProgram() :
            Program(glm::ivec2(640, 480), "GUI Demo", {}) {

    }

    virtual void start() {
        connect(window.signal_close, slot_stop);
        
        GUI::Font::LibraryT fonts({
            {"arial", GUI::Font::LibraryT::ResourceHandle(GUI::Font::Parameter("/usr/share/fonts/TTF/Hack-Regular.ttf", glm::vec2(12, 12), glm::ivec2(220, 220)))}
        });
        GUIMainMenu mainMenu(GUI, fonts);
        mainMenu.present();

        run();
    }
private:
};

int main(int argc, char **argv) {
    GUIProgram program = GUIProgram();

    program.start();

    return 0;
}
