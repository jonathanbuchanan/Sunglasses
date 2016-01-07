#include "FeatureScene.h"

FeatureScene::FeatureScene() {
	
}

void FeatureScene::initialize() {
	renderer.setSceneNode(this);
	renderer.setWindow(window);
	
	renderer.initialize();
	
	house = new SunObject("house", "/home/jonathan/Dev/sunglasses/Sample Projects/Feature/Resources/Graphics/Models/Cube.dae", false);
	
	this->addSubNode(house);
}

void FeatureScene::cycle(float delta) {
	renderer.render(delta);
}
