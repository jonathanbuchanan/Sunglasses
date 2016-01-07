#include "FeatureGame.h"

GLfloat _deltaTime = 0;
GLfloat _lastFrame = 0;

void FeatureGame::initialize() {
	SunGame::initialize();
	
	setWindowTitle("Feature");
	setClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	
	scene = FeatureScene();
	scene.initialize();
}

void FeatureGame::loop() {
	while (!glfwWindowShouldClose(window)) {
		GLfloat currentFrame = glfwGetTime();
    	_deltaTime = currentFrame - _lastFrame;
    	_lastFrame = currentFrame;
		
		scene.cycle(_deltaTime);
	}
}

void FeatureGame::cleanUp() {
	SunGame::cleanUp();
}
