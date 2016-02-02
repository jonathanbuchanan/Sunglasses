// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
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
