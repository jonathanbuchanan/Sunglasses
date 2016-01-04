#ifndef FeatureScene_H
#define FeatureScene_H

#include "SunScene.h"
#include "SunObject.h"

class FeatureScene : public SunScene {
public:
	FeatureScene();
	
	void initialize();
	
private:
	SunObject *house;
};

#endif
