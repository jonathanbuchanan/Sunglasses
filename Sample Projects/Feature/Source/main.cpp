// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "FeatureGame.h"
#include <Sunglasses/Sunglasses.hpp>

int main() {
    FeatureGame game = FeatureGame();
    game.initialize();

    game.run();

    game.cleanUp();

    return 0;
}
