// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunRenderer.h"
#include "../Core/SunScene.h"

void SunRenderer::render() {
    SunAction renderAction("render");
    renderAction.setRecursive(true);

    sendAction(renderAction, root);
}

void SunRenderer::swapBuffers() {
    // Swap the buffers
    services->get<SunWindowManager>()->swapBuffers();
}

void SunRenderer::init() {
    root = new SunNode();
}
