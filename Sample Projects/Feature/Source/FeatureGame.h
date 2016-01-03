#ifndef FEATUREGAME_H
#define FEATUREGAME_H

#include "SunGame.h"

#include "FeatureScene.h"

class FeatureGame : public SunGame {
public:
	FeatureGame() { }
	
	void initialize();
	void loop();
	void cleanUp();
private:
	FeatureScene scene;
};

#endif
