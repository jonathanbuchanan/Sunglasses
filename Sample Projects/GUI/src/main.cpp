// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "GUIGame.h"
#include <Sunglasses/Sunglasses.hpp>

int main(int argc, char **argv) {
    GUIGame game(argc, argv);

    game.run();

    return 0;
}
