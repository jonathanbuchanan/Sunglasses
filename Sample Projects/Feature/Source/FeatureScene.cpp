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
    
    house = new SunObject("house", "/home/jonathan/Dev/Sunglasses/Sample Projects/Feature/Resources/Graphics/Models/Cube.dae", false);
    
    rootRenderableNode->addSubNode(house);
    
    guiSystem = SunGUISystem();
    guiSystem.initializeDefaultPropertyAndFunctionMap();
    
    menu = new SunGUIMenu();
    guiSystem.addSubNode(menu);
    
    ((SunKeyboardManager *)(*services)["keyboard_manager"])->subscribe(menu, GLFW_KEY_ESCAPE, SunButtonEventDownSingle);
    
    auto show = [](SunNode *node) {
        ((SunGUIMenu *)node)->setVisible(!((SunGUIMenu *)node)->getVisible());
    };
    SunGUIAction showAction("Show", show);
    
    menu->addActionForKey(showAction, GLFW_KEY_ESCAPE);
    
    item = new SunGUIItem();
    menu->addSubNode(item);
    
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
    renderer.render(delta);
}
