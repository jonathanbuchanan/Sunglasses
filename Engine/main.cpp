// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <iostream>
#include "./SunGame.h"

#include <SFML/Audio.hpp>

SunGame game = SunGame();

int main(int argc, const char *argv[]) {
	std::cout << "Started" << std::endl;
    game.initialize(true, 4);
    
    game.loop();
	
	game.cleanUp();
    
    return 0;
}
