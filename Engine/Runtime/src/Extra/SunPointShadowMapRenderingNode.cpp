// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunPointShadowMapRenderingNode.h"

SunPointShadowMapRenderingNode::SunPointShadowMapRenderingNode() {

}

void SunPointShadowMapRenderingNode::init() {
    shadowMapShader = SunShader("./Graphics/Shaders/Variable Pipeline/Scene.vert", "./Graphics/Shaders/Variable Pipeline/Scene.geom", "./Graphics/Shaders/Variable Pipeline/Scene.frag", "./PointShadowMap.pre");

    addAction("loadPointLights", &SunPointShadowMapRenderingNode::loadPointLights);
    addAction("render", &SunPointShadowMapRenderingNode::render);
}

void SunPointShadowMapRenderingNode::loadPointLights(SunAction action) {
    // Action
    SunAction sceneAction("initializeShadowMapRenderer");

    // Renderer
    sceneAction.addParameter("renderer", this);

    //sendAction(sceneAction, scene);
}

void SunPointShadowMapRenderingNode::render(SunAction action) {
    // Action
    SunAction shadowMapAction("shadowMap");

    // Shader Map
    std::map<std::string, SunShader> shaderMap = {{"scene_all", shadowMapShader}};
    shadowMapAction.addParameter("shaderMap", &shaderMap);

    // Scene
    //shadowMapAction.addParameter("scene", scene);

    for (size_t i = 0; i < lights.size(); i++) {
        sendAction(shadowMapAction, lights[i]);
    }
}
