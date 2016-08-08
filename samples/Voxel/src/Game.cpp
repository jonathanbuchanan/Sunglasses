// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "Game.h"

void Game::init(int argc, char **argv) {
    SunGame::init(argc, argv, "Voxel", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)); 

    menuScene = new MenuScene();
    menuScene->init();

    gameScene = new GameScene();
    gameScene->init();
}

void Game::showMenuScene() {
    scene = menuScene;
}

void Game::showGameScene() {
    scene = gameScene;
}

void Game::loop() {

}
