// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunRenderer.h"
#include "../Core/SunScene.h"

void SunRenderer::render() {
    SunAction renderAction("render");
    renderAction.setRecursive(true);

    sendAction(renderAction, rootRenderNode.get());
}

void SunRenderer::swapBuffers() {
    // Swap the buffers
    ((SunWindowManager *)getService("window_manager"))->swapBuffers();
}

void SunRenderer::init() { }
