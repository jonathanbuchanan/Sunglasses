// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunScript.h"

SunScript::SunScript() {
    state = luaL_newstate();
    luaL_openlibs(state);
}

SunScript::~SunScript() {
    lua_close(state);
}

void SunScript::close() {
    lua_close(state);
}

void SunScript::loadFile(std::string file) {
    luaL_dofile(state, file.c_str());
}

_SunPrivateScripting::SunLuaValue SunScript::getVariable(std::string var) {
    return _SunPrivateScripting::SunLuaValue(state, var.c_str());
}

_SunPrivateScripting::SunLuaValue SunScript::operator[](std::string var) {
    return _SunPrivateScripting::SunLuaValue(state, var.c_str());
}

void SunScript::run(std::string code) {
    luaL_dostring(state, code.c_str());
}

void SunScript::operator()(std::string code) {
    run(code);
} 
