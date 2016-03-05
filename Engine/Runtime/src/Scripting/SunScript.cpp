// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunScript.h"

SunScript::SunScript() {
    state = new SunLuaState();
}

SunScript::~SunScript() {

}

void SunScript::loadFile(std::string file) {
    state->loadFile(file.c_str());
}

SunLuaValue SunScript::getVariable(std::string var) {
    return SunLuaValue(state, var.c_str());
}

SunLuaValue SunScript::operator[](std::string var) {
    return SunLuaValue(state, var.c_str());
}

void SunScript::run(std::string code) {
    state->run(code.c_str());
}

void SunScript::operator()(std::string code) {
    run(code);
}