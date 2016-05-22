// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGame.h"

#include "../Services.hpp"

#include "SunScene.h"

SunGame::SunGame() {

}

void SunGame::run() {
    while (!glfwWindowShouldClose(window)) {
        updateServices();
        services.get<SunWindowManager>()->calculateDelta();

        // Run the loop function (user defined logic goes here)
        loop();

        scene->cycle();
    }
}

void SunGame::updateServices() {
    for (auto &iterator : services.getServices()) {
        iterator.second->update();
    }
}

void SunGame::cleanUp() { /* THIS MUST BE IMPLEMENTED!!! */
    glfwTerminate();
}

void SunGame::init() {
    init(0, NULL, "", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
}


void SunGame::init(int argc, char **argv) {
    init(argc, argv, "", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
}

void SunGame::init(std::string title, glm::vec4 color) {
    init(0, NULL, title, color);
}

void SunGame::init(int argc, char **argv, std::string title, glm::vec4 color) {
    // Parse the command line options
    int width;
    int height;
    bool showCursor;
    SunCLValueOption<int> widthOpt("", "width", "The width of the window", "an integer value", 800, false, &width);
    SunCLValueOption<int> heightOpt("", "height", "The height of the window", "an integer value", 600, false, &height);
    SunCLSwitchOption cursorOpt("c", "cursor", "Show the cursor", false, &showCursor);
    std::vector<SunCLOption *> options = {
        &widthOpt,
        &heightOpt,
        &cursorOpt
    };
    
    parseOptions(options, "HELP MESSAGE", "alpha v0.0.1",  argc, argv);

    // Initialize the Audio Device Manager
    SunAudioDeviceManager *audioManager = new SunAudioDeviceManager();
    services.add(audioManager);

    // Initialize the Window Manager
    SunWindowManager *windowManager = new SunWindowManager(glm::vec2(width, height), title, color);
    windowManager->setName("window_manager");
    services.add(windowManager);
    window = windowManager->getWindow();

    // Initialize the Keyboard Manager
    SunKeyboardManager *keyboard = new SunKeyboardManager(window);
    keyboard->setName("keyboard_manager");
    services.add(keyboard);

    // Initialize the Cursor Manager
    SunCursorManager *cursor = new SunCursorManager(window, !showCursor);
    cursor->setName("cursor_manager");
    services.add(cursor);

    // Initialize the Mouse Button Manager
    SunMouseButtonManager *mouseButton = new SunMouseButtonManager(window);
    mouseButton->setName("mouse_button_manager");
    services.add(mouseButton);

    // Initialize the Logger
    SunLogger *logger = new SunLogger();
    logger->setName("logger");
    services.add(logger);

    // Initialize the Global Logic Environment
    SunGlobalScriptingEnvironment *globalEnvironment = new SunGlobalScriptingEnvironment();
    globalEnvironment->setName("global_logic_environment");
    services.add(globalEnvironment);

    // Initialize the Resource Management Service
    SunResourceService *resourceService = new SunResourceService();
    resourceService->setName("resource_service");
    services.add(resourceService);

    resourceService->addResourceManager("models", new SunResourceManager());
    resourceService->addResourceManager("meshes", new SunResourceManager());
    resourceService->addResourceManager("materials", new SunResourceManager());
    resourceService->addResourceManager("textures", new SunResourceManager());
    resourceService->addResourceManager("sounds", new SunResourceManager());
}
