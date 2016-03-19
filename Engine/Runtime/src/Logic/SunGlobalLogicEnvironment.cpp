// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGlobalLogicEnvironment.h"


#include "../Scripting/SunScript.h"
#include "../Core/SunObject.h"


SunGlobalLogicEnvironment::SunGlobalLogicEnvironment() {
    initialize();
}

void SunGlobalLogicEnvironment::initialize() {
    // Create the vec3 type
    registerType<glm::vec3>("vec3", "x", &glm::vec3::x, "y", &glm::vec3::y, "z", &glm::vec3::z);
    // Create the SunObject type
}

void SunGlobalLogicEnvironment::update() {

}

void SunGlobalLogicEnvironment::registerWithScript(SunScript *script) {
    script->registerObject("globalenvironment", this, "globalExists", &SunGlobalLogicEnvironment::globalExists, "setInteger", &SunGlobalLogicEnvironment::setInteger, "setBoolean", &SunGlobalLogicEnvironment::setBoolean, "setNumber", &SunGlobalLogicEnvironment::setNumber, "setString", &SunGlobalLogicEnvironment::setString, "getInteger", &SunGlobalLogicEnvironment::getInteger, "getBoolean", &SunGlobalLogicEnvironment::getBoolean, "getNumber", &SunGlobalLogicEnvironment::getNumber, "getString", &SunGlobalLogicEnvironment::getString);
}

void SunGlobalLogicEnvironment::registerGlobal(std::string key, _SunPrivateScripting::SunLuaPrimitive value) {
    globals[key] = value;
}

bool SunGlobalLogicEnvironment::globalExists(const char *key) {
    if (globals.find(std::string(key)) != globals.end())
        return true;
    else
        return false;
}

void SunGlobalLogicEnvironment::setInteger(const char *key, int value) {
    globals[key] = value;
}

void SunGlobalLogicEnvironment::setBoolean(const char *key, bool value) {
    globals[key] = value;
}

void SunGlobalLogicEnvironment::setNumber(const char *key, double value) {
    globals[key] = value;
}

void SunGlobalLogicEnvironment::setString(const char *key, const char *value) {
    globals[key] = value;
}

int SunGlobalLogicEnvironment::getInteger(const char *key) {
    return globals[key];
}

bool SunGlobalLogicEnvironment::getBoolean(const char *key) {
    return globals[key];
}

double SunGlobalLogicEnvironment::getNumber(const char *key) {
    return globals[key];
}

const char * SunGlobalLogicEnvironment::getString(const char *key) {
    return globals[std::string(key)];
}
