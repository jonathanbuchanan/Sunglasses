// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGUIItem.h"

void SunGUIItem::hide(SunNodeSentAction _action) {
    visible = false;
}

void SunGUIItem::show(SunNodeSentAction _action) {
    visible = true;
}

void SunGUIItem::toggleMouse(SunNodeSentAction _action) {
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void SunGUIItem::closeWindow(SunNodeSentAction _action) {
    glfwSetWindowShouldClose(window, true);
}

void SunGUIItem::initializeDefaultPropertyAndFunctionMap() {
    SunNode::initializeDefaultPropertyAndFunctionMap();

    addToFunctionMap("render", bind(&SunGUIItem::render, this, std::placeholders::_1));
    addToFunctionMap("hide", bind(&SunGUIItem::hide, this, std::placeholders::_1));
    addToFunctionMap("show", bind(&SunGUIItem::show, this, std::placeholders::_1));
    addToFunctionMap("toggleMouse", bind(&SunGUIItem::toggleMouse, this, std::placeholders::_1));
    addToFunctionMap("closeWindow", bind(&SunGUIItem::closeWindow, this, std::placeholders::_1));
}

void SunGUIItem::sendActions(map<string, GLboolean> _activeTriggers) {
    for (int i = 0; i < sentActions.size(); ++i) {
        if (_activeTriggers[*(string *) sentActions[i].properties["trigger"]] == true) {
            sendAction(sentActions[i], (SunNode *) sentActions[i].properties["receiver"]);
        }
    }
}

void SunGUIItem::render(SunNodeSentAction _action) {
    if (visible)
        mesh.render(position, size, color, textured, highlightColor, highlighted, text, font, (SunTextRenderer *) _action.parameters["textRenderer"]);
}

void SunGUIItem::loadTexture() {
    mesh.loadTexture(texturePath);
}

GLboolean SunGUIItem::pointInItem(glm::vec2 _point) {
    if (_point.x >= position.x && _point.x <= position.x + size.x && _point.y <= position.y + size.y && _point.y >= position.y)
        return true;
    return false;
}