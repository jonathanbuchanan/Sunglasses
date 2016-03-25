// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunScene.h"

#include "../Graphics/SunRenderer.h"

SunScene::SunScene() {

}

void SunScene::init() {

}

void SunScene::cycle() {
    SunAction update("update");
    update.setRecursive(true);
    sendAction(update, root);
    renderer->render();
    guiRenderer->render();
    renderer->swapBuffers();
}
