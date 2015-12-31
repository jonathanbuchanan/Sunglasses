#include "SunPointShadowMapRenderingNode.h"

SunPointShadowMapRenderingNode::SunPointShadowMapRenderingNode() {
	initializeDefaultPropertyAndFunctionMap();
}

void SunPointShadowMapRenderingNode::initialize() {
	
}

void SunPointShadowMapRenderingNode::initializeDefaultPropertyAndFunctionMap() {
	//SunRenderingNode::initializeDefaultPropertyAndFunctionMap();
	shadowMapShader = SunShader("./Graphics/Shaders/Variable Pipeline/Scene.vert", "./Graphics/Shaders/Variable Pipeline/Scene.geom", "./Graphics/Shaders/Variable Pipeline/Scene.frag", "./PointShadowMap.pre", "#version 330 core\n");
	
	addToFunctionMap("loadPointLights", bind(&SunPointShadowMapRenderingNode::loadPointLights, this, std::placeholders::_1));
	addToFunctionMap("render", bind(&SunPointShadowMapRenderingNode::render, this, std::placeholders::_1));
	addToFunctionMap("test", bind(&SunPointShadowMapRenderingNode::test, this, std::placeholders::_1));
}

void SunPointShadowMapRenderingNode::loadPointLights(SunNodeSentAction _action) {
	// Action
	SunNodeSentAction sceneAction;
	sceneAction.action = "initializeShadowMapRenderer";
	
	// Renderer
	sceneAction.parameters["renderer"] = this;
	
	sendAction(sceneAction, scene);
}

void SunPointShadowMapRenderingNode::render(SunNodeSentAction _action) {
	// Action
	SunNodeSentAction shadowMapAction;
	shadowMapAction.action = "shadowMap";
	
	// Delta Time
	shadowMapAction.parameters["deltaTime"] = _action.parameters["deltaTime"];
	
	// Shader Map
	map<string, SunShader> shaderMap = {{"scene_all", shadowMapShader}};
	shadowMapAction.parameters["shaderMap"] = &shaderMap;
	
	// Scene
	shadowMapAction.parameters["scene"] = scene;
	
	for (int i = 0; i < lights.size(); i++) {
		sendAction(shadowMapAction, lights[i]);
	}
}

void SunPointShadowMapRenderingNode::test(SunNodeSentAction _action) {
	SunRenderingNode::test(_action);
}
