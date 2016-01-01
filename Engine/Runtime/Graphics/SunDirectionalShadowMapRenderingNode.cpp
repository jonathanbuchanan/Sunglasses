// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunDirectionalShadowMapRenderingNode.h"

SunDirectionalShadowMapRenderingNode::SunDirectionalShadowMapRenderingNode() {
	initializeDefaultPropertyAndFunctionMap();
}

void SunDirectionalShadowMapRenderingNode::initialize() {
	
}

void SunDirectionalShadowMapRenderingNode::initializeDefaultPropertyAndFunctionMap() {
	//SunRenderingNode::initializeDefaultPropertyAndFunctionMap();
	shadowMapShader = SunShader("./Graphics/Shaders/Variable Pipeline/Scene.vert", "./Graphics/Shaders/Variable Pipeline/Scene.geom", "./Graphics/Shaders/Variable Pipeline/Scene.frag", "./DirectionalShadowMap.pre", "#version 330 core\n");
	
	addToFunctionMap("loadDirectionalLights", bind(&SunDirectionalShadowMapRenderingNode::loadDirectionalLights, this, std::placeholders::_1));
	addToFunctionMap("render", bind(&SunDirectionalShadowMapRenderingNode::render, this, std::placeholders::_1));
	addToFunctionMap("test", bind(&SunDirectionalShadowMapRenderingNode::test, this, std::placeholders::_1));
}

void SunDirectionalShadowMapRenderingNode::loadDirectionalLights(SunNodeSentAction _action) {
	// Action
	SunNodeSentAction sceneAction;
	sceneAction.action = "initializeShadowMapRenderer";
	
	// Renderer
	sceneAction.parameters["renderer"] = this;
	
	sendAction(sceneAction, scene);
}

void SunDirectionalShadowMapRenderingNode::render(SunNodeSentAction _action) {
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

void SunDirectionalShadowMapRenderingNode::test(SunNodeSentAction _action) {
	SunRenderingNode::test(_action);
}
