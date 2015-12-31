// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunRenderingNode.h"
#include "../SunPointLightObject.h"

#ifndef SunPointShadowMapRenderingNode_h
#define SunPointShadowMapRenderingNode_h

using namespace std;

class SunPointShadowMapRenderingNode : public SunRenderingNode {
public:
	SunPointShadowMapRenderingNode();
	
	virtual void initialize();
	virtual void initializeDefaultPropertyAndFunctionMap();
	void loadPointLights(SunNodeSentAction _action);
	virtual void render(SunNodeSentAction _action);
	
	virtual void test(SunNodeSentAction _action);
	
	inline vector<SunPointLightObject *> & getLights() { return lights; }
	inline SunPointLightObject * getLightAtIndex(int i) { return lights[i]; }
	inline void addLightToLights(SunPointLightObject *_p) { lights.push_back(_p); }
private:
	vector<SunPointLightObject *> lights;
	SunShader shadowMapShader;
};

#endif
