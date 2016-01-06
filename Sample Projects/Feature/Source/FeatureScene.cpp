#include "FeatureScene.h"

FeatureScene::FeatureScene() {
	
}

void FeatureScene::initialize() {
	renderer.initialize();
	
	house = new SunObject("house", "/home/jonathan/Dev/sunglasses/Sample Projects/Feature/Resources/Graphics/Models/Cube.dae", false);
	
	this->addSubNode(house);
}
