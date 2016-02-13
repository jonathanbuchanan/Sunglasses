// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunPointShadowMapRenderingNode.h"

SunPointShadowMapRenderingNode::SunPointShadowMapRenderingNode() {
	initializeDefaultPropertyAndFunctionMap();
}

void SunPointShadowMapRenderingNode::initialize() {
	
}

void SunPointShadowMapRenderingNode::initializeDefaultPropertyAndFunctionMap() {
	//SunRenderingNode::initializeDefaultPropertyAndFunctionMap();
	shadowMapShader = SunShader("./Graphics/Shaders/Variable Pipeline/Scene.vert", "./Graphics/Shaders/Variable Pipeline/Scene.geom", "./Graphics/Shaders/Variable Pipeline/Scene.frag", "./PointShadowMap.pre", "#version 330 core\n");
	
	addAction("loadPointLights", &SunPointShadowMapRenderingNode::loadPointLights);
	addAction("render", &SunPointShadowMapRenderingNode::render);	
}

void SunPointShadowMapRenderingNode::loadPointLights(SunAction action) {
	// Action
	SunAction sceneAction("initializeShadowMapRenderer");	
	
	// Renderer
	sceneAction.addParameter("renderer", this); 
	
	sendAction(sceneAction, scene);
}

void SunPointShadowMapRenderingNode::render(SunAction action) {
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
