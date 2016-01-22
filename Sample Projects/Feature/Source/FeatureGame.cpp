#include "FeatureGame.h"

GLfloat _deltaTime = 0;
GLfloat _lastFrame = 0;

void FeatureGame::initialize() {
	SunGame::initialize();
	
	setWindowTitle("Feature");
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
    	
    	glfwPollEvents();
		
		scene.cycle(_deltaTime);
	}
	glfwTerminate();
}

void FeatureGame::cleanUp() {
	SunGame::cleanUp();
}
