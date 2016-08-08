// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/SunRenderNode.h>
#include <iostream>


SunRenderNode::SunRenderNode() {

}

void SunRenderNode::init() {
    addAction("render", &SunRenderNode::render);
    addAction("bindOutputs", &SunRenderNode::bindOutputs);
}