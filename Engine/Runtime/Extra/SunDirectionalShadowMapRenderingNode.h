// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "Graphics/SunRenderingNode.h"
#include "SunDirectionalLight.h"

#ifndef SunDirectionalShadowMapRenderingNode_h
#define SunDirectionalShadowMapRenderingNode_h

using namespace std;

class SunDirectionalShadowMapRenderingNode : public SunRenderingNode {
public:
	SunDirectionalShadowMapRenderingNode();
	
	virtual void init(); 
	void loadDirectionalLights(SunAction action);
	virtual void render(SunAction action);
	
	inline vector<SunDirectionalLight *> & getLights() { return lights; }
	inline SunDirectionalLight * getLightAtIndex(int i) { return lights[i]; }
	inline void addLightToLights(SunDirectionalLight *_p) { lights.push_back(_p); }
private:
	vector<SunDirectionalLight *> lights;
	SunShader shadowMapShader;
};

#endif
