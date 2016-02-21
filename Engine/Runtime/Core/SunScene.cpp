// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunScene.h"

SunScene::SunScene() { 
    
}

void SunScene::init() { 

}

void SunScene::cycle(float delta) {
	SunAction update("update");
	update.addParameter("delta", &delta);
	update.setRecursive(true);
    sendAction(update, root);
	renderer->render(delta);
	guiRenderer->render();
	renderer->swapBuffers();
}
