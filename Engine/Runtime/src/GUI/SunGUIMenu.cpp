// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGUIMenu.h"
#include "../Logic/SunGlobalLogicEnvironment.h"

SunGUIMenu::SunGUIMenu() {

}

void SunGUIMenu::init() {
	addAction("render", &SunGUIMenu::render);
	addAction("key", &SunGUIMenu::key);
}

void SunGUIMenu::loadScript(std::string _script) {
    script.loadFile(_script);
    ((SunGlobalLogicEnvironment *)getService("global_logic_environment"))->registerWithScript(&script);
    script.registerObject("cursor_manager", ((SunCursorManager *)getService("cursor_manager")), "enableCursor", &SunCursorManager::enableCursor, "disableCursor", &SunCursorManager::disableCursor);
    script.registerObject("menu", this, "visible", &SunGUIMenu::visible);
}

void SunGUIMenu::render(SunAction action) {
    if (visible)
        sendActionToAllSubNodes(action);
}

void SunGUIMenu::key(SunAction action) {
    int key = action.getParameter<int>("key");
    script["keyPressed"](key);
}
