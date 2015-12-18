#include "SunRenderingNode.h"
#include "../SunPointLightObject.h"

#ifndef SunShadowMapRenderingNode_h
#define SunShadowMapRenderingNode_h

using namespace std;

class SunShadowMapRenderingNode : public SunRenderingNode {
public:
	SunShadowMapRenderingNode();
	
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
