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
	
	addAction("loadDirectionalLights", &SunDirectionalShadowMapRenderingNode::loadDirectionalLights);
	addAction("render", &SunDirectionalShadowMapRenderingNode::render);
}

void SunDirectionalShadowMapRenderingNode::loadDirectionalLights(SunAction action) {
	// Action
	SunAction sceneAction("initializeShadowMapRenderer");	
	
	// Renderer
	sceneAction.addParameter("renderer", this); 
	
	sendAction(sceneAction, scene);
}

void SunDirectionalShadowMapRenderingNode::render(SunAction action) {
	// Action
	SunAction shadowMapAction("shadowMap"); 
	
	// Delta Time
	shadowMapAction.addParameter("deltaTime", action.getParameter("deltaTime")); 
	
	// Shader Map
	map<string, SunShader> shaderMap = {{"scene_all", shadowMapShader}};
	shadowMapAction.addParameter("shaderMap", &shaderMap); 
	
	// Scene
	shadowMapAction.addParameter("scene", scene); 
	
	for (int i = 0; i < lights.size(); i++) {
		sendAction(shadowMapAction, lights[i]);
	}
} 
