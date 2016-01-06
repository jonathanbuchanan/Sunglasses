#ifndef FeatureScene_H
#define FeatureScene_H

#include "SunScene.h"
#include "SunObject.h"

#include "FeatureRenderer.h"

class FeatureScene : public SunScene {
public:
	FeatureScene();
	
	void initialize();
	
private:
	SunObject *house;
	
	FeatureRenderer renderer;
};

#endif
