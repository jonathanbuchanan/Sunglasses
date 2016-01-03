#include <iostream>
#include "FeatureGame.h"

int main() {
	FeatureGame game = FeatureGame();
	game.initialize();
	
	game.loop();
	
	game.cleanUp();
	
	return 0;
}
