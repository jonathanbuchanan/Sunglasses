// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "FeatureScene.h"

FeatureScene::FeatureScene() {

}

void FeatureScene::init() {
    this->setName("Scene");

    root = std::unique_ptr<SunNode>(new SunNode());
    root->setName("root");
    root->init();
    root->setIgnoreTags(true);

    std::shared_ptr<SunCamera> _camera = std::shared_ptr<SunCamera>(new SunCamera(45.0f, glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
    _camera->init();
    root->addSubNode(_camera);
    camera = _camera;

    ((SunGlobalLogicEnvironment *)getService("global_logic_environment"))->registerGlobal("doCameraInput", true);

    renderer = new FeatureRenderer();
    renderer->setSceneNode(this);
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

    std::shared_ptr<SunObject> teapot = std::shared_ptr<SunObject>(new SunObject("teapot0"));
    teapot->addTag("solid");
    teapot->newMesh("teapot", "Teapot", "teapotmaterial");
    teapot->loadScript("Scripts/Teapot.lua");
    teapot->init();
    teapot->setScale(glm::vec3(1.0f, 1.0f, 1.0f));

    teapots.push_back(teapot);
    root->addSubNode(teapot);

    std::shared_ptr<SunObject> _plane = std::shared_ptr<SunObject>(new SunObject("plane"));
    _plane->addTag("textured");
    _plane->newMesh("plane", "Plane.001", "planematerial", glm::vec3(0, 0, 0), glm::vec3(180, 0, 0), glm::vec3(10, 1, 10));
    _plane->init();
    _plane->setPosition(glm::vec3(0.0f, -7.0f, 0.0f));
    root->addSubNode(_plane);

    std::shared_ptr<SunShadowDirectionalLight> _dir = std::shared_ptr<SunShadowDirectionalLight>(new SunShadowDirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.2f, -1.0f, 0.4f)));
    _dir->setResolution(glm::ivec2(4096, 4096));
    _dir->setDistance(10.0f);
    _dir->setTarget(root.get());
    _dir->addTag("shadow_directional_light");
    _dir->init();
    root->addSubNode(_dir);
    dir = _dir;

    /*std::shared_ptr<SunShadowPointLight> point = std::shared_ptr<SunShadowPointLight>(new SunShadowPointLight(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 7.0f, 3.0f)));
    point->setResolution(2048);
    point->setTarget(root.get());
    point->addTag("shadow_point_light");
    point->init();
    root->addSubNode(point);
    pt = point;*/

    textRenderer = new SunTextRenderer();
    textRenderer->init();
    textRenderer->loadFont("Resources/Graphics/Fonts/arial.ttf", "Arial");
    std::shared_ptr<SunGUIMenu> _menu = std::shared_ptr<SunGUIMenu>(new SunGUIMenu());
    _menu->loadScript("Scripts/Menu0.lua");
    _menu->init();
    guiSystem.init();
    guiSystem.addSubNode(_menu);
    menu = _menu;

    guiRenderer = new SunGUIRenderer();
    guiRenderer->setGUIRoot(&guiSystem);
    guiRenderer->setTextRenderer(textRenderer);

    ((SunKeyboardManager *)getService("keyboard_manager"))->subscribe(_menu.get(), GLFW_KEY_ESCAPE, SunButtonEventDownSingle);

    std::shared_ptr<SunGUIItem> _item = std::shared_ptr<SunGUIItem>(new SunGUIItem());
    _item->init();
    _item->setScript(_menu.get());
    _menu->addSubNode(_item);
    item = _item;

    ((SunMouseButtonManager *)getService("mouse_button_manager"))->subscribe(_item.get(), GLFW_MOUSE_BUTTON_LEFT, SunButtonEventDownSingle);

    _item->addMouseActionForTrigger(GLFW_MOUSE_BUTTON_LEFT, "exitPressed");

    _item->setText("Exit");
    _item->setFont("Arial");
    _item->setSize(glm::vec2(1.0f, 0.2f));
    _item->setPosition(glm::vec2(-0.5f, -0.1f));
    _item->setColor(glm::vec3(1.0f, 1.0f, 1.0f));

    std::shared_ptr<SunGUIItem> _back = std::shared_ptr<SunGUIItem>(new SunGUIItem());
    _back->init();
    _back->setScript(_menu.get());
    _menu->addSubNode(_back);
    back = _back;

    ((SunMouseButtonManager *)getService("mouse_button_manager"))->subscribe(_back.get(), GLFW_MOUSE_BUTTON_LEFT, SunButtonEventDownSingle);

    _back->addMouseActionForTrigger(GLFW_MOUSE_BUTTON_LEFT, "hide");

    _back->setText("Back");
    _back->setFont("Arial");
    _back->setSize(glm::vec2(1.0f, 0.2f));
    _back->setPosition(glm::vec2(-0.5f, -0.4f));
    _back->setColor(glm::vec3(1.0f, 1.0f, 1.0f));

    SunAction registerAction("registerInScript");
    registerAction.setRecursive(true);

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
            teapot->setPosition(teapots[teapots.size() - 1].lock()->getPosition() + glm::vec3(7.0f, 0.0f, 0.0f));
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
