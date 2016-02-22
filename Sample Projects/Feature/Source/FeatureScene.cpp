// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "FeatureScene.h"

FeatureScene::FeatureScene() {
    
} 

void FeatureScene::init() {
	this->setName("Scene");

	root = new SunObject();
    root->setName("root");
    root->init();
	root->setIgnoreTags(true);

    camera = SunCamera(SunCameraProjectionTypePerspective, 45.0f, 0, 0, 0, 0);
	camera.init();
	root->addSubNode(&camera);

	initRenderer<FeatureRenderer>(); 
    renderer->setSceneNode(this);
	renderer->setWindow(window);
    renderer->initialize(); 

    house = new SunObject("cube", "/home/jonathan/Dev/Sunglasses/Sample Projects/Feature/Resources/Graphics/Models/Teapot.dae", "solid", false);
	house->init();
	house->setMaterial(SunObjectMaterial(glm::vec3(1.0f, 1.0f, 1.0f), 256.0f)); 
    root->addSubNode(house);

	light = new SunPointLight(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, -2.0f, 2.0f));
	light->setCountUniform("pointLightCount");
	light->setArrayUniform("pointLights");
	light->addTag("light");
	light->addTag("pointLight");
	root->addSubNode(light);

	dir = new SunDirectionalLight(glm::vec3(1.0f, 0.75f, 0.75f), glm::vec3(1.0f, -1.0f, 0.0f));
	dir->setCountUniform("directionalLightCount");
	dir->setArrayUniform("directionalLights");
	dir->addTag("light");
	dir->addTag("pointLight");
	root->addSubNode(dir);
    
	textRenderer = new SunTextRenderer();
    textRenderer->initialize(); 
    textRenderer->loadFont("Resources/Graphics/Fonts/arial.ttf", "Arial");
    menu = new SunGUIMenu();
	menu->init();
	guiSystem.init();
    guiSystem.addSubNode(menu);
    
	guiRenderer = new SunGUIRenderer();
	guiRenderer->setGUIRoot(&guiSystem);
	guiRenderer->setTextRenderer(textRenderer);

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
	item->init();
    item->setWindow(window);
    menu->addSubNode(item);
    
    ((SunMouseButtonManager *)getService("mouse_button_manager"))->subscribe(item, GLFW_MOUSE_BUTTON_LEFT, SunButtonEventDownSingle); 
    
    auto exit = [](SunBase *base) {
        SunGUIItem *item = (SunGUIItem *)base;
        if (item->cursorInItem())
			((SunWindowManager *)item->getService("window_manager"))->setWindowShouldClose();
    };
    SunLambdaAction exitAction(exit);
    
    item->addActionForKey(exitAction, GLFW_MOUSE_BUTTON_LEFT);
    
    item->setText("Exit");
    item->setFont("Arial");
    item->setSize(glm::vec2(1.0f, 0.2f));
    item->setPosition(glm::vec2(-0.5f, -0.1f));
    item->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
} 
