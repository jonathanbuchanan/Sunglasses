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

#include "./SunButtonState.h"

#include "./SunScene.h"

GLfloat lastX = 400;
GLfloat lastY = 300;
bool firstMouseTime = true;

// Maps containing GLFW button ids and their respective states
// NOTE: CLEAN UP OLDBUTTONS

map<int, SunButtonState> buttons;
map<int, SunButtonState> oldButtons;

GLfloat deltaTime = 0;
GLfloat lastFrame = 0;

GLfloat xOffset;
GLfloat yOffset;

GLfloat lastXOffset;
GLfloat lastYOffset;

// Called when a key is pressed

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    // If it had a transition, change its state
    
    if (action == GLFW_PRESS && buttons[key] != SunButtonStatePressedEdge) {
        buttons[key] = SunButtonStatePressedEdge;
    } else if (action == GLFW_RELEASE)
        buttons[key] = SunButtonStateReleased;
}

// Calculate the mouse position when it changes

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

// Called when a mouse button is pressed

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    // If it had a transition, change its state
    
    if (action == GLFW_PRESS)
        buttons[button] = SunButtonStatePressedEdge;
    else if (action == GLFW_RELEASE)
        buttons[button] = SunButtonStateReleased;
}

class SunGame {
public:
    SunScene *scene;
    
    GLFWwindow *window;
    
    GLfloat screenWidth = 800;
    GLfloat screenHeight = 600;
    
    SunGame() {
        
    }
    
    void loop() {
        // Loop until the game is set to close
        while (!glfwWindowShouldClose(window)) {
            // Calculate the frame time (NEEDS CLEAN UP)
            
            GLfloat currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            
            // Set old buttons (NEEDS CLEAN UP)
            
            oldButtons = buttons;
            
            // Poll GLFW events to check for any input
            
            glfwPollEvents();
            
            // Set any button that is pressed for the second cycle on to a different state (NEEDS CLEAN UP)
            
            for (auto iterator = buttons.begin(); iterator != buttons.end(); ++iterator) {
                int currentButton = iterator->first;
                
                SunButtonState currentValue = buttons[currentButton];
                SunButtonState oldValue = oldButtons[currentButton];
                
                if (currentValue == SunButtonStatePressedEdge && oldValue == SunButtonStatePressedEdge) {
                    buttons[currentButton] = SunButtonStatePressed;
                }
            }
            
            if (scene->doCameraInput == true) {
                // Tell the camera to do movement (NEEDS CLEAN UP)
                
                if (lastXOffset != xOffset && lastYOffset != yOffset)
                    scene->camera.doCameraMovement(buttons, deltaTime, xOffset, yOffset);
                if (lastXOffset == xOffset && lastYOffset != yOffset)
                    scene->camera.doCameraMovement(buttons, deltaTime, 0, yOffset);
                if (lastXOffset != xOffset && lastYOffset != yOffset)
                    scene->camera.doCameraMovement(buttons, deltaTime, xOffset, 0);
                else
                    scene->camera.doCameraMovement(buttons, deltaTime, 0, 0);
                
                lastXOffset = xOffset;
                lastYOffset = yOffset;
            } else {
                xOffset = lastXOffset;
                yOffset = lastYOffset;
            }
            
            // Tell the renderer to do its cycle
            
            scene->cycle(buttons, deltaTime);
        }
        glfwTerminate();
    }
    
    void initializeGLFWandGLEW(bool _useMSAA, GLint _MSAASampleCount) {
        // Initialize GLFW and give window hints
        
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
        }
        
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            std::cout << "Failed to initialize GLEW" << std::endl;
        }
        
        // Set the viewport size (NEEDS CLEAN UP)
        glViewport(0, 0, screenWidth * 2, screenHeight * 2);
        
        // Set the input callbacks
        glfwSetKeyCallback(window, keyCallback);
        glfwSetCursorPosCallback(window, mouseCallback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        
        // Set the mouse input mode
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
        // Enable depth testing
        glEnable(GL_DEPTH_TEST);
        
        // Enable multisampling
        if (_useMSAA == true) {
            glEnable(GL_MULTISAMPLE);
            glfwWindowHint(GLFW_SAMPLES, _MSAASampleCount);
        }
        
        // Enable hardware gamma correction
        glEnable(GL_FRAMEBUFFER_SRGB);
        
        // Enable blending;
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        scene = new SunScene("./SceneDemo.xml", window);
        
        // Set some properties of the renderer
        //renderer.window = window;
        
        //renderer.screenWidth = screenWidth;
        //renderer.screenHeight = screenHeight;
        
        // Tell the renderer to initialize
        //renderer.initialize();
    }
    
private:
    
    
};

#endif
