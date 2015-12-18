#include "SunShadowMapRenderingNode.h"

SunShadowMapRenderingNode::SunShadowMapRenderingNode() {
	initializeDefaultPropertyAndFunctionMap();
}

void SunShadowMapRenderingNode::initialize() {
	
}

void SunShadowMapRenderingNode::initializeDefaultPropertyAndFunctionMap() {
	//SunRenderingNode::initializeDefaultPropertyAndFunctionMap();
	shadowMapShader = SunShader("./Graphics/Shaders/Variable Pipeline/Scene.vert", "./Graphics/Shaders/Variable Pipeline/Scene.geom", "./Graphics/Shaders/Variable Pipeline/Scene.frag", "./PointShadowMap.pre", "#version 330 core\n");
	
	addToFunctionMap("loadPointLights", bind(&SunShadowMapRenderingNode::loadPointLights, this, std::placeholders::_1));
	addToFunctionMap("render", bind(&SunShadowMapRenderingNode::render, this, std::placeholders::_1));
	addToFunctionMap("test", bind(&SunShadowMapRenderingNode::test, this, std::placeholders::_1));
}

void SunShadowMapRenderingNode::loadPointLights(SunNodeSentAction _action) {
	// Action
	SunNodeSentAction sceneAction;
	sceneAction.action = "initializeShadowMapRenderer";
	
	// Renderer
	sceneAction.parameters["renderer"] = this;
	
	sendAction(sceneAction, scene);
}

void SunShadowMapRenderingNode::render(SunNodeSentAction _action) {
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

void SunShadowMapRenderingNode::test(SunNodeSentAction _action) {
	SunRenderingNode::test(_action);
}
