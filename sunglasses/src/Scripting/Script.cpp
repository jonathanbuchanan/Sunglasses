// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Scripting/Script.h>

namespace sunglasses {

Script::Script() {
    state = luaL_newstate();
    luaL_openlibs(state);
}

Script::~Script() {
    lua_close(state);
}

void Script::close() {
    lua_close(state);
}

void Script::loadFile(std::string file) {
    luaL_dofile(state, file.c_str());
}

_PrivateScripting::LuaValue Script::getVariable(std::string var) {
    return _PrivateScripting::LuaValue(state, var.c_str());
}

_PrivateScripting::LuaValue Script::operator[](std::string var) {
    return _PrivateScripting::LuaValue(state, var.c_str());
}

void Script::run(std::string code) {
    luaL_dostring(state, code.c_str());
}

void Script::operator()(std::string code) {
    run(code);
} 

} // namespace
