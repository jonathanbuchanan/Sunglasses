// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "Graphics/SunRenderingNode.h"
#include "SunPointLight.h"

#ifndef SunPointShadowMapRenderingNode_h
#define SunPointShadowMapRenderingNode_h

using namespace std;

class SunPointShadowMapRenderingNode : public SunRenderingNode {
public:
	SunPointShadowMapRenderingNode();
	
	virtual void init(); 
	void loadPointLights(SunAction action);
	virtual void render(SunAction action); 
	
	inline vector<SunPointLight *> & getLights() { return lights; }
	inline SunPointLight * getLightAtIndex(int i) { return lights[i]; }
	inline void addLightToLights(SunPointLight *_p) { lights.push_back(_p); }
private:
	vector<SunPointLight *> lights;
	SunShader shadowMapShader;
};

#endif
