// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <Sunglasses/Sunglasses.hpp>

#include "Game.h"

int main(int argc, char **argv) {
    Game game = Game();
    game.init(argc, argv);

    game.showGameScene();

    game.run();

    game.cleanUp();

    return 0;
}
