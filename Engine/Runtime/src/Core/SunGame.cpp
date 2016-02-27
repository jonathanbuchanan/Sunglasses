// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGame.h"

void SunGame::run() {
	while (!glfwWindowShouldClose(window)) {
		updateServices();
        ((SunWindowManager *)getService("window_manager"))->calculateDelta();
		
		// Run the loop function (user defined logic goes here)
		loop();

        scene->cycle();
    }
    glfwTerminate();
}

void SunGame::loop() {
	
}

void SunGame::updateServices() {
    for (auto iterator : services) {
        iterator.second->update();
    }
}

void SunGame::cleanUp() {
	glfwTerminate();
}

void SunGame::initialize(std::string title, glm::vec4 color) {
	// Initialize the Window Manager
	SunWindowManager *windowManager = new SunWindowManager(glm::vec2(800.0f, 600.0f), title, color);
	windowManager->name = "window_manager";
	addService(windowManager);
	window = windowManager->getWindow();
	
	// Initialize the Keyboard Manager
	SunKeyboardManager *keyboard = new SunKeyboardManager(window);
	keyboard->name = "keyboard_manager";
	addService(keyboard);
	
	// Initialize the Cursor Manager
	SunCursorManager *cursor = new SunCursorManager(window, true);
	cursor->name = "cursor_manager";
	addService(cursor);
	
	// Initialize the Mouse Button Manager
	SunMouseButtonManager *mouseButton = new SunMouseButtonManager(window);
	mouseButton->name = "mouse_button_manager";
	addService(mouseButton);
	
	// Initialize the Logger
	SunLogger *logger = new SunLogger();
	logger->name = "logger";
	addService(logger);	
}

void SunGame::initialize() {
	initialize("", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
}
