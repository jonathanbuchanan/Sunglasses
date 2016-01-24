#include "FeatureGame.h"

GLfloat _deltaTime = 0;
GLfloat _lastFrame = 0;

void FeatureGame::initialize() {
    setWindowTitle("Feature");
    
    SunGame::initialize();
    
    setClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
    
    scene = FeatureScene();
    scene.setWindow(window);
    scene.initialize();
}

void FeatureGame::loop() {
	while (!glfwWindowShouldClose(window)) {
            GLfloat currentFrame = glfwGetTime();
            _deltaTime = currentFrame - _lastFrame;
            _lastFrame = currentFrame;
            
            keyboard.update();
            
            scene.cycle(_deltaTime);
	}
	glfwTerminate();
}

void FeatureGame::cleanUp() {
	SunGame::cleanUp();
}
