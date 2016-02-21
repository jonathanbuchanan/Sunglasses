// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGUIRenderer.h"

SunGUIRenderer::SunGUIRenderer() {
	
}

void SunGUIRenderer::render() {
	// Render the GUI
	SunAction action("render");
	action.addParameter("textRenderer", textRenderer);
	sendAction(action, guiRoot);
}
