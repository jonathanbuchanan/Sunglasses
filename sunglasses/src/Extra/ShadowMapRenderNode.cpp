// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Extra/ShadowMapRenderNode.h>

namespace sunglasses {

ShadowMapRenderNode::ShadowMapRenderNode(Base *_target) : target(_target) {

}

void ShadowMapRenderNode::render(Action action) {
    for (auto &iterator : shaders) {
        iterator.second.use();

        Action shadowMap("shadowMap");
        shadowMap.setRecursive(true);
        shadowMap.addParameter("tag", &iterator.first);
        shadowMap.addParameter("shader", &iterator.second);

        sendAction(shadowMap, target);
    }
}

void ShadowMapRenderNode::bindOutputs(Action action) {

}

void ShadowMapRenderNode::addShader(std::string tag, graphics::Shader shader) {
    shaders.push_back(std::make_pair(tag, shader));
}

void ShadowMapRenderNode::setShaders(std::vector<std::pair<std::string, graphics::Shader>> _shaders) {
    shaders = _shaders;
}

} // namespace
