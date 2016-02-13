// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGUISystem.h"

void SunGUISystem::init() {
	addAction("render", &SunGUISystem::render); 
}

void SunGUISystem::render(SunAction action) {
    glEnable(GL_BLEND);

    // Loop through the sub-objects and force them to render
    sendActionToAllSubNodes(action);

    glDisable(GL_BLEND);
}

void SunGUISystem::loadFonts(SunTextRenderer *_textRenderer) {
    for (int i = 0; i < fonts.size(); i++) {
        _textRenderer->loadFont(fonts[i].file, fonts[i].name);
    }
    
    fontsLoaded = true;
}
