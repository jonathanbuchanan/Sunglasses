// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Extra/SunShadowMapRenderNode.h>

SunShadowMapRenderNode::SunShadowMapRenderNode(SunBase *_target) : target(_target) {

}

void SunShadowMapRenderNode::render(SunAction action) {
    for (auto &iterator : shaders) {
        iterator.second.use();

        SunAction shadowMap("shadowMap");
        shadowMap.setRecursive(true);
        shadowMap.addParameter("tag", &iterator.first);
        shadowMap.addParameter("shader", &iterator.second);

        sendAction(shadowMap, target);
    }
}

void SunShadowMapRenderNode::bindOutputs(SunAction action) {

}

void SunShadowMapRenderNode::addShader(std::string tag, SunShader shader) {
    shaders.push_back(std::make_pair(tag, shader));
}

void SunShadowMapRenderNode::setShaders(std::vector<std::pair<std::string, SunShader>> _shaders) {
    shaders = _shaders;
}
