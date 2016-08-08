// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "FeatureGame.h"
#include <sunglasses/Sunglasses.hpp>

int main(int argc, char **argp) {
    FeatureGame game = FeatureGame();
    game.init(argc, argp);

    game.run();

    game.cleanUp();

    return 0;
}
