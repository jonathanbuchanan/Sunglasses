// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SHADOWMAPRENDERNODE_H
#define SHADOWMAPRENDERNODE_H

#include "../Graphics/RenderNode.h"

namespace sunglasses {

class ShadowMapRenderNode : public RenderNode {
public:
    /// A constructor
    /**
     * @param _target The shadow map target
     */
    ShadowMapRenderNode(Base *_target);

    /// Renders the shadow maps.
    /**
     * This method sends a recursive 'shadowMap' action to the target. This action
     * causes shadow lights to render their shadow maps.
     */
    virtual void render(Action action);

    /// Binds the outputs of the render node.
    virtual void bindOutputs(Action action);

    /// Adds a shader for the given tag.
    void addShader(std::string tag, Shader shader);

    /// Sets the vector of shaders.
    void setShaders(std::vector<std::pair<std::string, Shader>> _shaders);
private:
    /// The shadow map target (usually the root node of the scene)
    Base *target;

    /// A vector of pairs of tags and shaders
    /**
     * At render time, a render action is sent out that has a tag for each respective
     * shader. This way, you can specify different shaders for different object by
     * choosing tags.
     */
    std::vector<std::pair<std::string, Shader>> shaders;
};

} // namespace

#endif
