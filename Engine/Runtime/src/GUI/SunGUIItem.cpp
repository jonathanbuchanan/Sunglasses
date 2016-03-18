// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGUIItem.h"
#include "SunGUIMenu.h"
#include "../Input/SunCursorManager.h"
#include "../Scripting/SunScript.h"

SunGUIItem::SunGUIItem() {
    mesh.setUpGL();
}

void SunGUIItem::init() {
	addAction("render", &SunGUIItem::render);
	addAction("button", &SunGUIItem::button);
}

void SunGUIItem::render(SunAction action) {
    if (visible)
        mesh.render(position, size, color, textured, highlightColor, highlighted, text, font, action.getParameterPointer<SunTextRenderer>("textRenderer"));
}

void SunGUIItem::button(SunAction action) {
    if (cursorInItem()) {
        int button = *(int *)action.getParameter("button");
        script->run(mouseActions[button] + "()");
    }
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
    glm::vec2 point = ((SunCursorManager *)getService("cursor_manager"))->getCursorPositionNDC();
    point.y = -point.y;
    return pointInItem(point);
}

void SunGUIItem::setScript(SunGUIMenu *m) {
    script = m->getScript();
}
