// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGUIItem.h"

SunGUIItem::SunGUIItem() {
    initializeDefaultPropertyAndFunctionMap();
    mesh.setUpGL();
}

void SunGUIItem::initializeDefaultPropertyAndFunctionMap() {
    SunNode::initializeDefaultPropertyAndFunctionMap();

    addToFunctionMap("render", bind(&SunGUIItem::render, this, std::placeholders::_1));
    addToFunctionMap("button", bind(&SunGUIItem::button, this, std::placeholders::_1));
}

void SunGUIItem::render(SunNodeSentAction _action) {
    if (visible)
        mesh.render(position, size, color, textured, highlightColor, highlighted, text, font, (SunTextRenderer *) _action.parameters["textRenderer"]);
}

void SunGUIItem::button(SunNodeSentAction _action) {
    int button = *(int *)_action.parameters["button"];
    
    actions[button].run(this);
}

void SunGUIItem::loadTexture() {
    mesh.loadTexture(texturePath);
}

bool SunGUIItem::pointInItem(glm::vec2 _point) {
    if (_point.x >= position.x && _point.x <= position.x + size.x && _point.y <= position.y + size.y && _point.y >= position.y)
        return true;
    return false;
}

bool SunGUIItem::cursorInItem() {
    return pointInItem(cursor->getCursorPositionNDC());
}