// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "FeatureGame.h"

GLfloat _deltaTime = 0;
GLfloat _lastFrame = 0;

void FeatureGame::initialize() {
    setWindowTitle("Feature");
    
    SunGame::initialize();
    
    setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	scene.setWindow(window);
    scene.init();
}

void FeatureGame::loop() {
    while (!glfwWindowShouldClose(window)) {
        GLfloat currentFrame = glfwGetTime();
        _deltaTime = currentFrame - _lastFrame;
        _lastFrame = currentFrame;
        
        SunGame::updateServices();
            
        scene.cycle(_deltaTime);
    }
    glfwTerminate();
}

void FeatureGame::cleanUp() {
    SunGame::cleanUp();
}
