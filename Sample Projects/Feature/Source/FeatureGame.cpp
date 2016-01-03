#include "FeatureGame.h"

void FeatureGame::initialize() {
	SunGame::initialize(false, 1);
}

void FeatureGame::loop() {
	SunGame::loop();
}

void FeatureGame::cleanUp() {
	SunGame::cleanUp();
}
