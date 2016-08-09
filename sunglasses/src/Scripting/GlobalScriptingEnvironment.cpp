// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Scripting/GlobalScriptingEnvironment.h>

#include <sunglasses/Scripting/Script.h>
#include <sunglasses/Core/Object.h>

#include <sunglasses/Core/ServiceManager.h>

#include <sunglasses/Input/CursorManager.h>
#include <sunglasses/Input/KeyboardManager.h>
#include <sunglasses/Input/MouseButtonManager.h>

#include <sunglasses/Graphics/WindowManager.h>

#include <map>
#include <string>

namespace sunglasses {

template<> const std::string LuaTypeRegistrar<GlobalScriptingEnvironment>::typeName = "GlobalScriptingEnvironment";
template<> const std::map<std::string, Scripting::LuaTypeDataMemberBase<GlobalScriptingEnvironment> *> LuaTypeRegistrar<GlobalScriptingEnvironment>::dataMembers = {
    {"globalExists", new LuaTypeMemberFunction<GlobalScriptingEnvironment, bool, const char *>("globalExists", &GlobalScriptingEnvironment::globalExists)},
    {"setInteger", new LuaTypeMemberFunction<GlobalScriptingEnvironment, void, const char *, int>("setInteger", &GlobalScriptingEnvironment::setInteger)},
    {"setBoolean", new LuaTypeMemberFunction<GlobalScriptingEnvironment, void, const char *, bool>("setBoolean", &GlobalScriptingEnvironment::setBoolean)},
    {"setNumber", new LuaTypeMemberFunction<GlobalScriptingEnvironment, void, const char *, double>("setNumber", &GlobalScriptingEnvironment::setNumber)},
    {"setString", new LuaTypeMemberFunction<GlobalScriptingEnvironment, void, const char *, const char *>("setString", &GlobalScriptingEnvironment::setString)},
    {"getInteger", new LuaTypeMemberFunction<GlobalScriptingEnvironment, int, const char *>("getInteger", &GlobalScriptingEnvironment::getInteger)},
    {"getBoolean", new LuaTypeMemberFunction<GlobalScriptingEnvironment, bool, const char *>("getBoolean", &GlobalScriptingEnvironment::getBoolean)},
    {"getNumber", new LuaTypeMemberFunction<GlobalScriptingEnvironment, double, const char *>("getNumber", &GlobalScriptingEnvironment::getNumber)},
    {"getString", new LuaTypeMemberFunction<GlobalScriptingEnvironment, const char *, const char *>("getString", &GlobalScriptingEnvironment::getString)}
};

GlobalScriptingEnvironment::GlobalScriptingEnvironment() {
    initialize();
}

void GlobalScriptingEnvironment::initialize() {

}

void GlobalScriptingEnvironment::update() {

}

void GlobalScriptingEnvironment::registerObject(Object *object) {
    objects.push_back(object);
    for (size_t i = 0; i < scripts.size(); ++i) {
        object->registerInScript(scripts[i], (*scripts[i])["a"]);
        //Script *script = scripts[i];
        /*script->registerObject(script->getVariable("globalenvironment")[object->getName().c_str()], object);
        script->registerObjectAsType(script->getVariable("globalenvironment")[object->getName().c_str()]["rotation"], "vec3", &object->rotation);
        script->registerObjectAsType(script->getVariable("globalenvironment")[object->getName().c_str()]["position"], "vec3", &object->position);
        script->registerObjectAsType(script->getVariable("globalenvironment")[object->getName().c_str()]["scale"], "vec3", &object->scale);*/
        // FIX ME
        //script->registerObjectAsType(script->getVariable("globalenvironment")[object->getName().c_str()]["color"], "vec3", &object->material.color);
    }
}

int GlobalScriptingEnvironment::removeObject(Object *object) {
    if (std::find(objects.begin(), objects.end(), object) == objects.end())
        return -1;
    else {
        std::string name = object->getName();
        scripts.erase(std::remove(scripts.begin(), scripts.end(), &object->script), scripts.end());
        objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
        /*for (size_t i = 0; i < scripts.size(); ++i) {
            Script *script = scripts[i];
        }*/
    }
    return 0;
}

void GlobalScriptingEnvironment::registerServices(ServiceManager &services, Script &script) {
    iterateTypes<CursorManager, KeyboardManager, MouseButtonManager, WindowManager>(services, script);
}

void GlobalScriptingEnvironment::registerGlobal(std::string key, _PrivateScripting::LuaPrimitive value) {
    globals[key] = value;
}

bool GlobalScriptingEnvironment::globalExists(const char *key) {
    if (globals.find(std::string(key)) != globals.end())
        return true;
    else
        return false;
}

void GlobalScriptingEnvironment::setInteger(const char *key, int value) {
    globals[key] = value;
}

void GlobalScriptingEnvironment::setBoolean(const char *key, bool value) {
    globals[key] = value;
}

void GlobalScriptingEnvironment::setNumber(const char *key, double value) {
    globals[key] = value;
}

void GlobalScriptingEnvironment::setString(const char *key, const char *value) {
    globals[key] = value;
}

int GlobalScriptingEnvironment::getInteger(const char *key) {
    return globals[key];
}

bool GlobalScriptingEnvironment::getBoolean(const char *key) {
    return globals[key];
}

double GlobalScriptingEnvironment::getNumber(const char *key) {
    return globals[key];
}

const char * GlobalScriptingEnvironment::getString(const char *key) {
    return globals[std::string(key)];
}

}
