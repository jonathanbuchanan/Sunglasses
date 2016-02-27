// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef FEATUREGAME_H
#define FEATUREGAME_H

#include "FeatureScene.h"
#include "Sunglasses.hpp"

class FeatureGame : public SunGame {
public:
    FeatureGame() { }

    void initialize();
    void loop();
    void cleanUp();
};

#endif
