// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "GameScene.h"

#include "GameRenderer.h"

void GameScene::init() {
    root = std::unique_ptr<World>(new World());
    root->init();

    std::shared_ptr<SunCamera> camera = std::shared_ptr<SunCamera>(new SunCamera(45.0f, glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
    camera->init();
    root->addSubNode(camera);

    renderer = new GameRenderer();
    renderer->setSceneNode(this);
    renderer->init();

    textRenderer = new SunTextRenderer();
    textRenderer->init();
    //textRenderer->loadFont("res/Graphics/Fonts/arial.ttf", "Arial");

    guiSystem.init();

    guiRenderer = new SunGUIRenderer();
    guiRenderer->setGUIRoot(&guiSystem);
    guiRenderer->setTextRenderer(textRenderer);
}
