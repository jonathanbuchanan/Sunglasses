#include "FeatureGame.h"

void FeatureGame::initialize() {
	SunGame::initialize();
	
	setWindowTitle("Feature");
	setClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	
	scene = FeatureScene();
	scene.initialize();
}

void FeatureGame::loop() {
	SunGame::loop();
}

void FeatureGame::cleanUp() {
	SunGame::cleanUp();
}
