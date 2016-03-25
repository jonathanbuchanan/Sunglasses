// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "FeatureGame.h"

void FeatureGame::init() {
    SunGame::init("Feature", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    scene = new FeatureScene();
    scene->setWindow(window);
    scene->init();
}

void FeatureGame::loop() {
    // Put your loop functionality here
}

void FeatureGame::cleanUp() {
    SunGame::cleanUp();
}
