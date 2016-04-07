// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNSHADOWMAPRENDERNODE_H
#define SUNSHADOWMAPRENDERNODE_H

#include "../Graphics/SunRenderNode.h"

class SunShadowMapRenderNode : public SunRenderNode {
public:
    /// A constructor
    /**
     * @param _target The shadow map target
     */
    SunShadowMapRenderNode(SunBase *_target);

    /// Renders the shadow maps.
    /**
     * This method sends a recursive 'shadowMap' action to the target. This action
     * causes shadow lights to render their shadow maps.
     */
    virtual void render(SunAction action);

    /// Binds the outputs of the render node.
    virtual void bindOutputs(SunAction action);

    /// Adds a shader for the given tag.
    void addShader(std::string tag, SunShader shader);

    /// Sets the vector of shaders.
    void setShaders(std::vector<std::pair<std::string, SunShader>> _shaders);
private:
    /// The shadow map target (usually the root node of the scene)
    SunBase *target;

    /// A vector of pairs of tags and shaders
    /**
     * At render time, a render action is sent out that has a tag for each respective
     * shader. This way, you can specify different shaders for different object by
     * choosing tags.
     */
    std::vector<std::pair<std::string, SunShader>> shaders;
};

#endif
