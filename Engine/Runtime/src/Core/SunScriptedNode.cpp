// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunScriptedNode.h"

SunScriptedNode::SunScriptedNode() {

}

SunScriptedNode::SunScriptedNode(std::string file) {
    loadFile(file);
}

void SunScriptedNode::loadFile(std::string file) {
    state.Load(file);
}

void SunScriptedNode::run(const char *code) {
    state(code);
}

void SunScriptedNode::operator()(const char *code) {
    run(code);
}
