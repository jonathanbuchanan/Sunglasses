#ifndef FEATUREGAME_H
#define FEATUREGAME_H

//#include "../../../Engine/Runtime/SunGame.h"
#include "SunGame.h"

class FeatureGame : public SunGame {
public:
	FeatureGame() { }
	
	void initialize();
	void loop();
	void cleanUp();
	
private:
};

#endif
