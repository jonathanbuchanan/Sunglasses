// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/RenderNode.h>
#include <iostream>

namespace sunglasses {

RenderNode::RenderNode() {

}

void RenderNode::init() {
    addAction("render", &RenderNode::render);
    addAction("bindOutputs", &RenderNode::bindOutputs);
}

} // namespace
