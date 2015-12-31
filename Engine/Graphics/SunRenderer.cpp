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

