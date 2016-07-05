// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GAME_H
#define GAME_H

#include <sunglasses/Sunglasses.hpp>

#include "MenuScene.h"

#include "GameScene.h"

class Game : public SunGame {
public:
    void init(int argc, char **argv);

    void showMenuScene();

    void showGameScene();

    virtual void loop();
private:
    MenuScene *menuScene;

    GameScene *gameScene;
};

#endif
