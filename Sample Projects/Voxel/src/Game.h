#ifndef GAME_H
#define GAME_H

#include <Sunglasses/Sunglasses.hpp>

#include "MenuScene.h"

class Game : public SunGame {
public:
    Game();

    void showMenuScene();

    virtual void loop();
private:

};

#endif
