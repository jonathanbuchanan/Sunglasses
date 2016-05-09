// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "GameScene.h"

#include "GameRenderer.h"

void GameScene::init() {
    root = std::unique_ptr<World>(new World());

    renderer = new GameRenderer();
    renderer->setSceneNode(this);
    renderer->init();

    textRenderer = new SunTextRenderer();
    textRenderer->init();
    //textRenderer->loadFont("Resources/Graphics/Fonts/arial.ttf", "Arial");

    guiSystem.init();

    guiRenderer = new SunGUIRenderer();
    guiRenderer->setGUIRoot(&guiSystem);
    guiRenderer->setTextRenderer(textRenderer);
}
