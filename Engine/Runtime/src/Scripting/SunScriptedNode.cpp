// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunScriptedNode.h"

SunScriptedNode::SunScriptedNode() {
    state = luaL_newstate();
    luaL_openlibs(state);
}

void SunScriptedNode::loadFile(std::string file) {
    luaL_dofile(state, file.c_str());
}

SunLuaValue SunScriptedNode::getVariable(std::string var) {
    return SunLuaValue(state, var.c_str());
}

SunLuaValue SunScriptedNode::operator[](std::string var) {
    return SunLuaValue(state, var.c_str());
}

void SunScriptedNode::run(std::string code) {
    luaL_dostring(state, code.c_str());
}

void SunScriptedNode::operator()(std::string code) {
    run(code);
}

/*SunScriptedNode & SunScriptedNode::operator=(const SunScriptedNode &source) {
    SunNode::operator=(source);
    return *this;
}
*/
