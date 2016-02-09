// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "FeatureScene.h"

FeatureScene::FeatureScene() {
    
}

void FeatureScene::initializeDefaultPropertyAndFunctionMap() {
    addToFunctionMap("render", bind(&FeatureScene::render, this, std::placeholders::_1));
    addToFunctionMap("renderGUI", bind(&FeatureScene::renderGUI, this, std::placeholders::_1));
    addToFunctionMap("passPerFrameUniforms", bind(&SunScene::passPerFrameUniformsAction, this, std::placeholders::_1));
}

void FeatureScene::initialize() {
    setRotation(glm::vec3(0, 0, 0));
    setScale(glm::vec3(1.0, 1.0, 1.0));
    setRootNode(this);
    
    camera = SunCamera(SunCameraProjectionTypePerspective, 45.0f, 0, 0, 0, 0);
    camera.setKeyboardManager((SunKeyboardManager *)(*services)["keyboard_manager"]);
    camera.setCursorManager((SunCursorManager *)(*services)["cursor_manager"]);
    
    this->setName("Scene");
    initializeDefaultPropertyAndFunctionMap();
    setPosition(glm::vec3(0, 0, 0));
    
    renderer.setSceneNode(this);
    renderer.setWindow(window);
    
    renderer.initialize();
    
    rootRenderableNode = new SunObject();
    rootRenderableNode->setName("RootRenderableNode");
    rootRenderableNode->initializeDefaultPropertyAndFunctionMap();
    addSubNode(rootRenderableNode);
    
    house = new SunObject("cube", "/home/jonathan/Dev/Sunglasses/Sample Projects/Feature/Resources/Graphics/Models/Cube.dae", false);
    
    rootRenderableNode->addSubNode(house);
    
    textRenderer.initialize();
    textRenderer.loadFont("Resources/Graphics/Fonts/arial.ttf", "Arial");
    
    menu = new SunGUIMenu();
    guiSystem.addSubNode(menu);
    
    ((SunKeyboardManager *)(*services)["keyboard_manager"])->subscribe(menu, GLFW_KEY_ESCAPE, SunButtonEventDownSingle);
    menu->setCursorManager((SunCursorManager *)(*services)["cursor_manager"]);
    
    auto show = [](SunNode *node) {
        SunGUIMenu *menu = (SunGUIMenu *)node;
        menu->setVisible(!((SunGUIMenu *)node)->getVisible());
        
        if (menu->getCursorManager()->getMode() == GLFW_CURSOR_DISABLED) {
            menu->getCursorManager()->enableCursor();
        } else if (menu->getCursorManager()->getMode() == GLFW_CURSOR_NORMAL) {
            menu->getCursorManager()->disableCursor();
        }
    };
    SunGUIAction showAction("Show", show);
    
    menu->addActionForKey(showAction, GLFW_KEY_ESCAPE);
    
    item = new SunGUIItem();
    item->setWindow(window);
    menu->addSubNode(item);
    
    ((SunMouseButtonManager *)(*services)["mouse_button_manager"])->subscribe(item, GLFW_MOUSE_BUTTON_LEFT, SunButtonEventDownSingle);
    item->setCursorManager((SunCursorManager *)(*services)["cursor_manager"]);
    
    auto exit = [](SunNode *node) {
        SunGUIItem *item = (SunGUIItem *)node;
        if (item->cursorInItem())
            glfwSetWindowShouldClose(item->getWindow(), true);
    };
    SunGUIAction exitAction("Exit", exit);
    
    item->addActionForKey(exitAction, GLFW_MOUSE_BUTTON_LEFT);
    
    item->setText("Exit");
    item->setFont("Arial");
    item->setSize(glm::vec2(1.0f, 0.2f));
    item->setPosition(glm::vec2(-0.5f, -0.1f));
    item->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
}

void FeatureScene::render(SunNodeSentAction _action) {
    SunScene::render(_action);
}

void FeatureScene::renderGUI(SunNodeSentAction _action) {
    SunNodeSentAction GUIAction;
    GUIAction.action = "render";
    GUIAction.parameters["textRenderer"] = &textRenderer;
    
    sendAction(GUIAction, &guiSystem);
}

void FeatureScene::cycle(float delta) {
    camera.update(delta);
    renderer.render(delta);
}
