// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Core/SunScene.h>

#include <sunglasses/Graphics/SunRenderer.h>

SunScene::SunScene() {

}

void SunScene::init() {

}

void SunScene::cycle() {
    SunAction update("update");
    update.setRecursive(true);
    sendAction(update, root.get());
    renderer->render();
    renderer->swapBuffers();
}
