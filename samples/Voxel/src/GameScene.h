// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <sunglasses/Sunglasses.hpp>

#include "World.h"

class GameScene : public SunScene {
public:
    void init();
private:
    SunGUISystem guiSystem = SunGUISystem();
};

#endif
