#include "FeatureScene.h"

FeatureScene::FeatureScene() {
    
}

void FeatureScene::initializeDefaultPropertyAndFunctionMap() {
    addToFunctionMap("render", bind(&FeatureScene::render, this, std::placeholders::_1));
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
    
    SunGUIMenu *menu = new SunGUIMenu();
    guiSystem.addSubNode(menu);
    
    ((SunKeyboardManager *)(*services)["keyboard_manager"])->subscribe(menu, GLFW_KEY_F);
}

void FeatureScene::render(SunNodeSentAction _action) {
    SunScene::render(_action);
}

void FeatureScene::cycle(float delta) {
    renderer.render(delta);
    
    SunNodeSentAction GUIAction;
    GUIAction.action = "render";
    GUIAction.parameters["textRenderer"] = &textRenderer;
    
    sendAction(GUIAction, &guiSystem);
}
