// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGame.h"

GLfloat screenWidth = 800;
GLfloat screenHeight = 600;

#ifdef RETINA
screenWidth = 1600;
screenHeight = 1200;
#endif

GLfloat deltaTime = 0;
GLfloat lastFrame = 0;

void SunGame::loop() {
    while (!glfwWindowShouldClose(window)) {
        // Calculate the frame time (NEEDS CLEAN UP)

        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
    glfwTerminate();
}

void SunGame::updateServices() {
    for (auto iterator : services) {
        iterator.second->update();
    }
}

void SunGame::cleanUp() {
	glfwTerminate();
}

void SunGame::initialize() {
    // Initialize GLFW and give window hints
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(screenWidth, screenHeight, windowTitle.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    
    // Initialize the Keyboard Manager
    SunKeyboardManager *keyboard = new SunKeyboardManager(window);
    keyboard->name = "keyboard_manager";
    addService(keyboard);
    
    // Initialize the Cursor Manager
    SunCursorManager *cursor = new SunCursorManager(window, false);
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

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
    }

    // Set the viewport size (NEEDS CLEAN UP)
    glViewport(0, 0, screenWidth, screenHeight);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable hardware gamma correction
    glEnable(GL_FRAMEBUFFER_SRGB);

    // Set blending function
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set the clear color
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);	
}
