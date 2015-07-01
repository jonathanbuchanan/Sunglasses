//
//  SunGame.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/16/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_SunGame_h
#define OpenGL_Test_3_SunGame_h

#include <iostream>
#include <unistd.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "SunButtonState.h"

#include "SunRenderer.h"

GLfloat lastX = 400;
GLfloat lastY = 300;
bool firstMouseTime = true;

map<int, SunButtonState> buttons;
map<int, SunButtonState> oldButtons;

GLfloat deltaTime = 0;
GLfloat lastFrame = 0;

GLfloat xOffset;
GLfloat yOffset;

GLfloat lastXOffset;
GLfloat lastYOffset;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS && buttons[key] != SunButtonStatePressedEdge) {
        buttons[key] = SunButtonStatePressedEdge;
    } else if (action == GLFW_RELEASE)
        buttons[key] = SunButtonStateReleased;
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouseTime) {
        lastX = xpos;
        lastY = ypos;
        firstMouseTime = false;
    }
    
    xOffset = xpos - lastX;
    yOffset = lastY - ypos;
    
    lastX = xpos;
    lastY = ypos;
    
    GLfloat sensitivity = 0.15;
    xOffset *= sensitivity;
    yOffset *= sensitivity;
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    if (action == GLFW_PRESS)
        buttons[button] = SunButtonStatePressedEdge;
    else if (action == GLFW_RELEASE)
        buttons[button] = SunButtonStateReleased;
}

class SunGame {
public:
    SunRenderer renderer;
    
    GLFWwindow *window;
    
    GLfloat screenWidth = 800;
    GLfloat screenHeight = 600;
    
    SunGame() {
        renderer = SunRenderer();
    }
    
    void loop() {
        while (!glfwWindowShouldClose(window)) {
            GLfloat currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            
            oldButtons = buttons;
            
            glfwPollEvents();
            
            for (auto iterator = buttons.begin(); iterator != buttons.end(); ++iterator) {
                int currentButton = iterator->first;
                
                SunButtonState currentValue = buttons[currentButton];
                SunButtonState oldValue = oldButtons[currentButton];
                
                if (currentValue == SunButtonStatePressedEdge && oldValue == SunButtonStatePressedEdge) {
                    buttons[currentButton] = SunButtonStatePressed;
                }
            }
            
            if (lastXOffset != xOffset && lastYOffset != yOffset)
                renderer.camera.doCameraMovement(buttons, deltaTime, xOffset, yOffset);
            if (lastXOffset == xOffset && lastYOffset != yOffset)
                renderer.camera.doCameraMovement(buttons, deltaTime, 0, yOffset);
            if (lastXOffset != xOffset && lastYOffset != yOffset)
                renderer.camera.doCameraMovement(buttons, deltaTime, xOffset, 0);
            else
                renderer.camera.doCameraMovement(buttons, deltaTime, 0, 0);
            
            lastXOffset = xOffset;
            lastYOffset = yOffset;
            
            renderer.cycle(buttons, deltaTime);
        }
        glfwTerminate();
    }
    
    void initializeGLFWandGLEW(bool _useMSAA, GLint _MSAASampleCount) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        if (_useMSAA == true)
            glfwWindowHint(GLFW_SAMPLES, _MSAASampleCount);
        
        window = glfwCreateWindow(screenWidth, screenHeight, "Sunglasses", nullptr, nullptr);
        glfwMakeContextCurrent(window);
        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return -1;
        }
        
        glViewport(0, 0, screenWidth * 2, screenHeight * 2);
        
        glfwSetKeyCallback(window, keyCallback);
        glfwSetCursorPosCallback(window, mouseCallback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        
        if (_useMSAA == true) {
            glEnable(GL_MULTISAMPLE);
            glfwWindowHint(GLFW_SAMPLES, _MSAASampleCount);
        }
        // Enable Hardware Gamma Correction
        glEnable(GL_FRAMEBUFFER_SRGB);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        renderer.window = window;
        
        renderer.screenWidth = screenWidth;
        renderer.screenHeight = screenHeight;
        
        renderer.initialize();
    }
    
private:
    
    
};

#endif
