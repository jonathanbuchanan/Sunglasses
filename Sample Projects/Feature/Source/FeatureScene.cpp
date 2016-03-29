// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "FeatureScene.h"

FeatureScene::FeatureScene() {

}

void FeatureScene::init() {
    this->setName("Scene");

	root = new SunNode();
    root->setName("root");
    root->init();
    root->setIgnoreTags(true);

    camera = std::shared_ptr<SunCamera>(new SunCamera(45.0f, glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
	camera->init();
	root->addSubNode(camera);

    ((SunGlobalLogicEnvironment *)getService("global_logic_environment"))->registerGlobal("doCameraInput", true);

    renderer = new FeatureRenderer();
    renderer->setSceneNode(this);
    renderer->setWindow(window);
    renderer->init();

    ((SunResourceService *)getService("resource_service"))->addResourceManager("models", new SunResourceManager());
    ((SunResourceService *)getService("resource_service"))->addResourceManager("meshes", new SunResourceManager());
    ((SunResourceService *)getService("resource_service"))->addResourceManager("materials", new SunResourceManager());
    ((SunResourceService *)getService("resource_service"))->addResourceManager("textures", new SunResourceManager());

    std::map<std::string, SunResource *> meshMap;

    ((SunResourceService *)getService("resource_service"))->getResourceManager("models")->addResource("teapot", new SunModelResource("Resources/Graphics/Models/Teapot.dae", &meshMap));
    ((SunResourceService *)getService("resource_service"))->getResourceManager("meshes")->addResources(meshMap);
    meshMap.clear();

    ((SunResourceService *)getService("resource_service"))->getResourceManager("models")->addResource("plane", new SunModelResource("Resources/Graphics/Models/Plane.dae", &meshMap));
    ((SunResourceService *)getService("resource_service"))->getResourceManager("meshes")->addResources(meshMap);
    meshMap.clear();

    ((SunResourceService *)getService("resource_service"))->getResourceManager("textures")->addResource("grass", new SunTextureResource("Resources/Graphics/Textures/grass.png"));

    SunTextureResource *grassTexture = (SunTextureResource *)((SunResourceService *)getService("resource_service"))->getResourceManager("textures")->getResource("grass");

    ((SunResourceService *)getService("resource_service"))->getResourceManager("materials")->addResource("teapotmaterial", new SunMaterialResource(glm::vec3(1.0f, 1.0f, 1.0f), 1024.0f));

    ((SunResourceService *)getService("resource_service"))->getResourceManager("materials")->addResource("planematerial", new SunMaterialResource(grassTexture, 4.0f));

    std::shared_ptr<SunObject>teapot = std::shared_ptr<SunObject>(new SunObject("teapot0"));
    teapot->addTag("solid");
    teapot->newMesh("teapot", "Teapot", "teapotmaterial");
    teapot->loadScript("Scripts/Teapot.lua");
    teapot->init();
    teapot->setScale(glm::vec3(1.0f, 1.0f, 1.0f));

    teapots.push_back(teapot);
    root->addSubNode(teapot);

    plane = std::shared_ptr<SunObject>(new SunObject("plane"));
    plane->addTag("textured");
    plane->newMesh("plane", "Plane.001", "planematerial", glm::vec3(0, 0, 0), glm::vec3(180, 0, 0), glm::vec3(10, 1, 10));
	plane->init();
	plane->setPosition(glm::vec3(0.0f, -7.0f, 0.0f));
	root->addSubNode(plane);

	dir = std::shared_ptr<SunDirectionalLight>(new SunDirectionalLight(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(4.0f, -4.0f, 2.0f)));
	dir->setCountUniform("directionalLightCount");
	dir->setArrayUniform("directionalLights");
	dir->addTag("light");
	root->addSubNode(dir);
	(std::static_pointer_cast<SunDirectionalShadowMapRenderingNode>(renderer->getRenderingNodeForString("shadowMap0")))->setLight(dir.get());
	(std::static_pointer_cast<SunDirectionalShadowMapRenderingNode>(renderer->getRenderingNodeForString("shadowMap0")))->setResolution(glm::vec2(4096.0f, 4096.0f));
	(std::static_pointer_cast<SunDirectionalShadowMapRenderingNode>(renderer->getRenderingNodeForString("shadowMap0")))->setSize(glm::vec2(50.0f, 50.0f));

    (std::static_pointer_cast<SunDirectionalShadowMapRenderingNode>(renderer->getRenderingNodeForString("shadowMap0")))->init();

    textRenderer = new SunTextRenderer();
    textRenderer->init();
    textRenderer->loadFont("Resources/Graphics/Fonts/arial.ttf", "Arial");
    menu = std::shared_ptr<SunGUIMenu>(new SunGUIMenu());
    menu->loadScript("Scripts/Menu0.lua");
    menu->init();
    guiSystem.init();
    guiSystem.addSubNode(menu);

    guiRenderer = new SunGUIRenderer();
    guiRenderer->setGUIRoot(&guiSystem);
    guiRenderer->setTextRenderer(textRenderer);

    ((SunKeyboardManager *)getService("keyboard_manager"))->subscribe(menu.get(), GLFW_KEY_ESCAPE, SunButtonEventDownSingle);

    item = std::shared_ptr<SunGUIItem>(new SunGUIItem());
    item->init();
    item->setScript(menu.get());
    menu->addSubNode(item);

    ((SunMouseButtonManager *)getService("mouse_button_manager"))->subscribe(item.get(), GLFW_MOUSE_BUTTON_LEFT, SunButtonEventDownSingle);

    item->addMouseActionForTrigger(GLFW_MOUSE_BUTTON_LEFT, "exitPressed");

    item->setText("Exit");
    item->setFont("Arial");
    item->setSize(glm::vec2(1.0f, 0.2f));
    item->setPosition(glm::vec2(-0.5f, -0.1f));
    item->setColor(glm::vec3(1.0f, 1.0f, 1.0f));

    back = std::shared_ptr<SunGUIItem>(new SunGUIItem());
    back->init();
    back->setScript(menu.get());
    menu->addSubNode(back);

    ((SunMouseButtonManager *)getService("mouse_button_manager"))->subscribe(back.get(), GLFW_MOUSE_BUTTON_LEFT, SunButtonEventDownSingle);

    back->addMouseActionForTrigger(GLFW_MOUSE_BUTTON_LEFT, "hide");

    back->setText("Back");
    back->setFont("Arial");
    back->setSize(glm::vec2(1.0f, 0.2f));
    back->setPosition(glm::vec2(-0.5f, -0.4f));
    back->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
}

void FeatureScene::cycle() {
    SunScene::cycle();
    static bool idown = false;
    static bool odown = false;
    SunKeyboardManager *keyboard = ((SunKeyboardManager *)getService("keyboard_manager"));
    if (keyboard->pollKey(GLFW_KEY_I) == true && idown == false) {
        SunObject *teapot = new SunObject("teapot" + std::to_string(teapots.size()));
        teapot->addTag("solid");
        teapot->newMesh("teapot", "Teapot", "teapotmaterial");
        if (teapots.size() > 0)
            teapot->setPosition(teapots[teapots.size() - 1]->getPosition() + glm::vec3(7.0f, 0.0f, 0.0f));
        teapot->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
        teapot->loadScript("Scripts/Teapot.lua");
        teapot->init();
        root->addSubNode(teapot);
        //teapots.push_back(teapot);
        idown = true;
    }
    if (keyboard->pollKey(GLFW_KEY_I) == false)
        idown = false;
    if (keyboard->pollKey(GLFW_KEY_O) == true && odown == false) {
        //((SunGlobalLogicEnvironment *)getService("global_logic_environment"))->removeObject(teapots[teapots.size() - 1]);
        //root->recursiveDeleteSubnode(teapots[teapots.size() - 1]);
        //delete teapots[teapots.size() - 1];
        //teapots.pop_back();
        odown = true;
    }
    if (keyboard->pollKey(GLFW_KEY_O) == false)
        odown = false;
}
