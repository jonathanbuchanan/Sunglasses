// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunRenderer.h"

void SunRenderer::render(GLfloat _deltaTime) {
    SunNodeSentAction renderAction;
    renderAction.action = "render";
    renderAction.parameters["deltaTime"] = &_deltaTime;
    renderAction.recursive = true;

    sendAction(renderAction, rootRenderNode);

    // Render the GUI
    SunNodeSentAction action;
    action.action = "renderGUISystem";

    sendAction(action, scene);

    // Swap the buffers
    swapBuffers();
}

void SunRenderer::swapBuffers() {
    // Swap the buffers
    glfwSwapBuffers(window);
}

