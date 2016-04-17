// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGlobalScriptingEnvironment.h"

#include "../Scripting/SunScript.h"
#include "../Core/SunObject.h"

SunGlobalScriptingEnvironment::SunGlobalScriptingEnvironment() {
    initialize();
}

void SunGlobalScriptingEnvironment::initialize() {

}

void SunGlobalScriptingEnvironment::update() {

}

void SunGlobalScriptingEnvironment::registerObject(SunObject *object) {
    objects.push_back(object);
    for (size_t i = 0; i < scripts.size(); ++i) {
        object->registerInScript(scripts[i], (*scripts[i])["a"]);
        SunScript *script = scripts[i];
        /*script->registerObject(script->getVariable("globalenvironment")[object->getName().c_str()], object);
        script->registerObjectAsType(script->getVariable("globalenvironment")[object->getName().c_str()]["rotation"], "vec3", &object->rotation);
        script->registerObjectAsType(script->getVariable("globalenvironment")[object->getName().c_str()]["position"], "vec3", &object->position);
        script->registerObjectAsType(script->getVariable("globalenvironment")[object->getName().c_str()]["scale"], "vec3", &object->scale);*/
        // FIX ME
        //script->registerObjectAsType(script->getVariable("globalenvironment")[object->getName().c_str()]["color"], "vec3", &object->material.color);
    }
}

int SunGlobalScriptingEnvironment::removeObject(SunObject *object) {
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

void SunGlobalScriptingEnvironment::registerWithScript(SunScript &script) {
    script.registerType<glm::vec3>("vec3", "x", &glm::vec3::x, "y", &glm::vec3::y, "z", &glm::vec3::z);
    script.registerObject("globalenvironment", this, "globalExists", &SunGlobalScriptingEnvironment::globalExists, "setInteger", &SunGlobalScriptingEnvironment::setInteger, "setBoolean", &SunGlobalScriptingEnvironment::setBoolean, "setNumber", &SunGlobalScriptingEnvironment::setNumber, "setString", &SunGlobalScriptingEnvironment::setString, "getInteger", &SunGlobalScriptingEnvironment::getInteger, "getBoolean", &SunGlobalScriptingEnvironment::getBoolean, "getNumber", &SunGlobalScriptingEnvironment::getNumber, "getString", &SunGlobalScriptingEnvironment::getString);
    std::vector<std::string> registered;
    //script[i]
    for (size_t i = 0; i < objects.size(); ++i) {
        objects[i]->registerInScript(&script, script[objects[i]->getName()]);
    }
    scripts.push_back(&script);
}

void SunGlobalScriptingEnvironment::registerGlobal(std::string key, _SunPrivateScripting::SunLuaPrimitive value) {
    globals[key] = value;
}

bool SunGlobalScriptingEnvironment::globalExists(const char *key) {
    if (globals.find(std::string(key)) != globals.end())
        return true;
    else
        return false;
}

void SunGlobalScriptingEnvironment::setInteger(const char *key, int value) {
    globals[key] = value;
}

void SunGlobalScriptingEnvironment::setBoolean(const char *key, bool value) {
    globals[key] = value;
}

void SunGlobalScriptingEnvironment::setNumber(const char *key, double value) {
    globals[key] = value;
}

void SunGlobalScriptingEnvironment::setString(const char *key, const char *value) {
    globals[key] = value;
}

int SunGlobalScriptingEnvironment::getInteger(const char *key) {
    return globals[key];
}

bool SunGlobalScriptingEnvironment::getBoolean(const char *key) {
    return globals[key];
}

double SunGlobalScriptingEnvironment::getNumber(const char *key) {
    return globals[key];
}

const char * SunGlobalScriptingEnvironment::getString(const char *key) {
    return globals[std::string(key)];
}
