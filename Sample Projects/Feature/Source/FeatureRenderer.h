#ifndef FEATURERENDERER_H
#define FEATURERENDERER_H

#include "Graphics/SunRenderer.h"
#include <vector>

class FeatureRenderer : public SunRenderer {
public:
	
	void initialize();
	
	void render(float delta);
private:
	GLFWwindow *window;
};

#endif
