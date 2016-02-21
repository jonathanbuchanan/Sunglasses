// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunRenderer.h"
#include "Core/SunScene.h"

void SunRenderer::render(GLfloat _deltaTime) {
	SunAction renderAction("render");
	renderAction.addParameter("delta", &_deltaTime);
	renderAction.setRecursive(true);

    sendAction(renderAction, rootRenderNode); 
}

void SunRenderer::swapBuffers() {
    // Swap the buffers
    glfwSwapBuffers(window);
}

void SunRenderer::initialize() { }
