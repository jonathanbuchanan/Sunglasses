// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNRENDERNODE_H
#define SUNRENDERNODE_H

#include <vector>
#include <map>
#include <functional>


#include "../Core/SunNode.h"
#include "SunShader.h"


/// An abstract class for defining rendering behavior.
/**
 * This abstract class is used to define rendering behavior. To define render
 * behavior, override the render member function. You must also override the bindOutputs
 * member function, which prepares the outputs for the next render node.
 */
class SunRenderNode : public SunNode {
public:
    /// The default constructor
    SunRenderNode();

    /// This function initializes the render node.
    /**
     * When subclassing SunRenderNode, always call SunRenderNode::init() to guarantee
     * that the 'render' action is added.
     */
    virtual void init();

    /// This function performs the rendering.
    /**
     * This function is used to perform rendering. You must override this to
     * subclass SunRenderNode. When subclassing, you must also call bindOutputs, on
     * all the parent nodes.
     */
    virtual void render(SunAction action) = 0;

    /// This function binds the outputs for the next node.
    /**
     * This function is used to prepare the output of the current node for the
     * next one's job. You must overrid this to subclass SunRenderNode. The
     * action should have a parameter named 'shader' that should be a pointer
     * to the shader to bind to.
     */
    virtual void bindOutputs(SunAction action) = 0;
};

#endif
