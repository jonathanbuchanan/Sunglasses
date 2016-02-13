// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGUIMenu.h"

SunGUIMenu::SunGUIMenu() {

}

void SunGUIMenu::init() {
	addAction("render", &SunGUIMenu::render);
	addAction("key", &SunGUIMenu::key); 
}

void SunGUIMenu::render(SunAction action) {
    if (visible)
        sendActionToAllSubNodes(action);
}

void SunGUIMenu::key(SunAction action) {
    int key = *(int *)action.getParameter("key");
    
    actions[key].run(this);
}
