// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <iostream>
#include "FeatureGame.h"

int main() {
    FeatureGame game = FeatureGame();
    game.initialize();
    
    game.loop();
    
    game.cleanUp();
    
    return 0;
}
