// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunRenderingNode.h"
#include "SunDirectionalLightObject.h"

#ifndef SunDirectionalShadowMapRenderingNode_h
#define SunDirectionalShadowMapRenderingNode_h

using namespace std;

class SunDirectionalShadowMapRenderingNode : public SunRenderingNode {
public:
	SunDirectionalShadowMapRenderingNode();
	
	virtual void initialize();
	virtual void initializeDefaultPropertyAndFunctionMap();
	void loadDirectionalLights(SunAction action);
	virtual void render(SunAction action);
	
	inline vector<SunDirectionalLightObject *> & getLights() { return lights; }
	inline SunDirectionalLightObject * getLightAtIndex(int i) { return lights[i]; }
	inline void addLightToLights(SunDirectionalLightObject *_p) { lights.push_back(_p); }
private:
	vector<SunDirectionalLightObject *> lights;
	SunShader shadowMapShader;
};

#endif
