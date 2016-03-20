// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunScript.h"

SunScript::SunScript() {
    state = new _SunPrivateScripting::SunLuaState();
}

SunScript::~SunScript() {

}

void SunScript::close() {
    state->close();
}

void SunScript::loadFile(std::string file) {
    state->loadFile(file.c_str());
}

_SunPrivateScripting::SunLuaValue SunScript::getVariable(std::string var) {
    return _SunPrivateScripting::SunLuaValue(state, var.c_str());
}

_SunPrivateScripting::SunLuaValue SunScript::operator[](std::string var) {
    return _SunPrivateScripting::SunLuaValue(state, var.c_str());
}

void SunScript::run(std::string code) {
    state->run(code.c_str());
}

void SunScript::operator()(std::string code) {
    run(code);
}

void SunScript::_addObject(std::shared_ptr<_SunPrivateScripting::_SunLuaObject_Base> object) {
    objects.push_back(object);
}
