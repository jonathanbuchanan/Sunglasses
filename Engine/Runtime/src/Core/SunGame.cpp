// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGame.h"

#include "../Graphics/SunWindowManager.h"
#include "../Input/SunKeyboardManager.h"
#include "../Input/SunCursorManager.h"
#include "../Input/SunMouseButtonManager.h"
#include "../Output/SunLogger.h"
#include "../Logic/SunGlobalLogicEnvironment.h"

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
    for (auto iterator : services) {
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
    bool x = false;
    std::string name;
    SunCLSwitchOption switchOpt("s", "switch", "Test", false, &x);
    SunCLValueOption<std::string> nameOpt("n", "name", "Your name", "a string", "Jonathan", false, &name);
    std::vector<SunCLOption *> options = {
        &switchOpt,
        &nameOpt
    };

    parseOptions(options, argc, argv);

    std::cout << x << std::endl;
    std::cout << name << std::endl;

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
}
