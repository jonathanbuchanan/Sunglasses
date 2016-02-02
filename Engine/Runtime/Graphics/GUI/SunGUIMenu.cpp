// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGUIMenu.h"

SunGUIMenu::SunGUIMenu() {
    initializeDefaultPropertyAndFunctionMap();
}

void SunGUIMenu::initializeDefaultPropertyAndFunctionMap() {
    addToFunctionMap("render", std::bind(&SunGUIMenu::render, this, std::placeholders::_1));
    addToFunctionMap("key", std::bind(&SunGUIMenu::key, this, std::placeholders::_1));
}

void SunGUIMenu::render(SunNodeSentAction _action) {
    if (visible)
        sendActionToAllSubNodes(_action);
}

void SunGUIMenu::key(SunNodeSentAction _action) {
    int key = *(int *)_action.parameters["key"];
    
    actions[key].run(this);
}