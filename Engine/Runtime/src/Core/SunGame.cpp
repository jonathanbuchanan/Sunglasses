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
        ((SunWindowManager *)getService("window_manager"))->calculateDelta();

        // Run the loop function (user defined logic goes here)
        loop();

        scene->cycle();
    }
}

void SunGame::updateServices() {
    for (auto &iterator : services) {
        iterator.second->update();
    }
}

void SunGame::cleanUp() { /* THIS MUST BE IMPLEMENTED!!! */
    glfwTerminate();
}

void SunGame::init(std::string title, glm::vec4 color) {
    // Initialize the Window Manager
    SunWindowManager *windowManager = new SunWindowManager(glm::vec2(800.0f, 600.0f), title, color);
    windowManager->setName("window_manager");
    addService(windowManager);
    window = windowManager->getWindow();

    // Initialize the Keyboard Manager
    SunKeyboardManager *keyboard = new SunKeyboardManager(window);
    keyboard->setName("keyboard_manager");
    addService(keyboard);

    // Initialize the Cursor Manager
    SunCursorManager *cursor = new SunCursorManager(window, true);
    cursor->setName("cursor_manager");
    addService(cursor);

    // Initialize the Mouse Button Manager
    SunMouseButtonManager *mouseButton = new SunMouseButtonManager(window);
    mouseButton->setName("mouse_button_manager");
    addService(mouseButton);

    // Initialize the Logger
    SunLogger *logger = new SunLogger();
    logger->setName("logger");
    addService(logger);

    // Initialize the Global Logic Environment
    SunGlobalLogicEnvironment *globalEnvironment = new SunGlobalLogicEnvironment();
    globalEnvironment->setName("global_logic_environment");
    addService(globalEnvironment);

    // Initialize the Resource Management Service
    SunResourceService *resourceService = new SunResourceService();
    resourceService->setName("resource_service");
    addService(resourceService);
}

void SunGame::init() {
    init("", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
}
