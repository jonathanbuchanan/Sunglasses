#include <iostream>
#include "./SunGame.h"

#include <SFML/Audio.hpp>

SunGame game = SunGame();

int main(int argc, const char *argv[]) {
    game.initialize(true, 4);
    
    game.loop();
    
    return 0;
}