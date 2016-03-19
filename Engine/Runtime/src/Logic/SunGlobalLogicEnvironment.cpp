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
    for (size_t i = 0; i < scripts.size(); i++) {
        std::shared_ptr<SunScript> script = scripts[i].first;
        std::vector<std::string> &registered = scripts[i].second;
        for (size_t j = 0; j < objects.size(); j++) {
            if (std::find(registered.begin(), registered.end(), objects[j]->getName()) == registered.end()) {
                script->registerObject(script->getVariable("globalenvironment")[objects[j]->getName().c_str()], objects[i].get());
                script->registerObjectAsType(script->getVariable("globalenvironment")[objects[j]->getName().c_str()]["rotation"], "vec3", &objects[j]->rotation);
                script->registerObjectAsType(script->getVariable("globalenvironment")[objects[j]->getName().c_str()]["position"], "vec3", &objects[j]->position);
                script->registerObjectAsType(script->getVariable("globalenvironment")[objects[j]->getName().c_str()]["scale"], "vec3", &objects[j]->scale);
                script->registerObjectAsType(script->getVariable("globalenvironment")[objects[j]->getName().c_str()]["color"], "vec3", &objects[j]->material.color);
                registered.push_back(objects[j]->getName());
            }
        }
    }
}

void SunGlobalLogicEnvironment::registerObject(SunObject *object) {
    objects.push_back(std::shared_ptr<SunObject>(object));
}

void SunGlobalLogicEnvironment::registerWithScript(SunScript *script) {
    script->registerType<glm::vec3>("vec3", "x", &glm::vec3::x, "y", &glm::vec3::y, "z", &glm::vec3::z);
    script->registerObject("globalenvironment", this, "globalExists", &SunGlobalLogicEnvironment::globalExists, "setInteger", &SunGlobalLogicEnvironment::setInteger, "setBoolean", &SunGlobalLogicEnvironment::setBoolean, "setNumber", &SunGlobalLogicEnvironment::setNumber, "setString", &SunGlobalLogicEnvironment::setString, "getInteger", &SunGlobalLogicEnvironment::getInteger, "getBoolean", &SunGlobalLogicEnvironment::getBoolean, "getNumber", &SunGlobalLogicEnvironment::getNumber, "getString", &SunGlobalLogicEnvironment::getString);
    std::vector<std::string> registered;
    scripts.push_back(std::make_pair(std::shared_ptr<SunScript>(script), registered));
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
