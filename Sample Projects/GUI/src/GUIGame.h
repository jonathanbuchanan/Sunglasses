// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GUIGAME_H
#define GUIGAME_H

#include <sunglasses/Sunglasses.hpp>

#include "GUIMainMenu.h"

class GUIGame : public SunGame {
public:
    GUIGame(int argc, char **argv);

    void loop();
private:
    GUIMainMenu mainMenu;
};

#endif
