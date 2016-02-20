// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "FeatureScene.h"

FeatureScene::FeatureScene() {
    
} 

void FeatureScene::init() { 
	addAction("renderGUI", &FeatureScene::renderGUI);
	addAction("passPerFrameUniforms", &FeatureScene::passPerFrameUniformsAction);
    
    camera = SunCamera(SunCameraProjectionTypePerspective, 45.0f, 0, 0, 0, 0);

    this->setName("Scene");
   
	root = new SunObject();
    root->setName("root");
    root->init();

    renderer.setSceneNode(this);
    renderer.setWindow(window);
    
    renderer.initialize(); 
    
    house = new SunObject("cube", "/home/jonathan/Dev/Sunglasses/Sample Projects/Feature/Resources/Graphics/Models/Cube.dae", "solid");
    
    root->addSubNode(house);
    
    textRenderer.initialize(); 
    textRenderer.loadFont("Resources/Graphics/Fonts/arial.ttf", "Arial");
    menu = new SunGUIMenu();
    guiSystem.addSubNode(menu);
    
    ((SunKeyboardManager *)getService("keyboard_manager"))->subscribe(menu, GLFW_KEY_ESCAPE, SunButtonEventDownSingle); 
    
    auto show = [](SunBase *base) {
        SunGUIMenu *menu = (SunGUIMenu *)base;
        menu->setVisible(!menu->getVisible());
        
        if (((SunCursorManager *)menu->getService("cursor_manager"))->getMode() == GLFW_CURSOR_DISABLED) {
            ((SunCursorManager *)menu->getService("cursor_manager"))->enableCursor();
        } else if (((SunCursorManager *)menu->getService("cursor_manager"))->getMode() == GLFW_CURSOR_NORMAL) {
            ((SunCursorManager *)menu->getService("cursor_manager"))->disableCursor();
        }
    };
    SunLambdaAction showAction(show);
    
    menu->addActionForKey(showAction, GLFW_KEY_ESCAPE);
    
    item = new SunGUIItem();
    item->setWindow(window);
    menu->addSubNode(item);
    
    ((SunMouseButtonManager *)getService("mouse_button_manager"))->subscribe(item, GLFW_MOUSE_BUTTON_LEFT, SunButtonEventDownSingle); 
    
    auto exit = [](SunBase *base) {
        SunGUIItem *item = (SunGUIItem *)base;
        if (item->cursorInItem())
            glfwSetWindowShouldClose(item->getWindow(), true);
    };
    SunLambdaAction exitAction(exit);
    
    item->addActionForKey(exitAction, GLFW_MOUSE_BUTTON_LEFT);
    
    item->setText("Exit");
    item->setFont("Arial");
    item->setSize(glm::vec2(1.0f, 0.2f));
    item->setPosition(glm::vec2(-0.5f, -0.1f));
    item->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
} 

void FeatureScene::renderGUI(SunAction action) {
    SunAction GUIAction;
    GUIAction.setAction("render");
	GUIAction.addParameter("textRenderer", &textRenderer); 
    
    sendAction(GUIAction, &guiSystem);
}

void FeatureScene::cycle(float delta) {
    camera.update(delta);
    renderer.render(delta);
}
