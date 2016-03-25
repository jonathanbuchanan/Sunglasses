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

}

void SunGlobalLogicEnvironment::update() {

}

void SunGlobalLogicEnvironment::registerObject(SunObject *object) {
    objects.push_back(object);
    for (size_t i = 0; i < scripts.size(); ++i) {
        SunScript *script = scripts[i];
        script->registerObject(script->getVariable("globalenvironment")[object->getName().c_str()], object);
        script->registerObjectAsType(script->getVariable("globalenvironment")[object->getName().c_str()]["rotation"], "vec3", &object->rotation);
        script->registerObjectAsType(script->getVariable("globalenvironment")[object->getName().c_str()]["position"], "vec3", &object->position);
        script->registerObjectAsType(script->getVariable("globalenvironment")[object->getName().c_str()]["scale"], "vec3", &object->scale);
        // FIX ME
        //script->registerObjectAsType(script->getVariable("globalenvironment")[object->getName().c_str()]["color"], "vec3", &object->material.color);
    }
}

int SunGlobalLogicEnvironment::removeObject(SunObject *object) {
    if (std::find(objects.begin(), objects.end(), object) == objects.end())
        return -1;
    else {
        std::string name = object->getName();
        scripts.erase(std::remove(scripts.begin(), scripts.end(), &object->script), scripts.end());
        objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
        /*for (size_t i = 0; i < scripts.size(); ++i) {
            SunScript *script = scripts[i];
        }*/
    }
    return 0;
}

void SunGlobalLogicEnvironment::registerWithScript(SunScript *script) {
    script->registerType<glm::vec3>("vec3", "x", &glm::vec3::x, "y", &glm::vec3::y, "z", &glm::vec3::z);
    script->registerObject("globalenvironment", this, "globalExists", &SunGlobalLogicEnvironment::globalExists, "setInteger", &SunGlobalLogicEnvironment::setInteger, "setBoolean", &SunGlobalLogicEnvironment::setBoolean, "setNumber", &SunGlobalLogicEnvironment::setNumber, "setString", &SunGlobalLogicEnvironment::setString, "getInteger", &SunGlobalLogicEnvironment::getInteger, "getBoolean", &SunGlobalLogicEnvironment::getBoolean, "getNumber", &SunGlobalLogicEnvironment::getNumber, "getString", &SunGlobalLogicEnvironment::getString);
    std::vector<std::string> registered;
    scripts.push_back(script);
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
