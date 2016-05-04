// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunObject.h"

#include "../Graphics/SunWindowManager.h"
#include "../Graphics/Loaders/SunMaterialResource.h"
#include "../Input/SunKeyboardManager.h"
#include "../Scripting/SunGlobalScriptingEnvironment.h"
#include "../Extern/SunResourceService.h"

template<> const std::string SunLuaTypeRegistrar<SunObject>::typeName = "Object";
template<> const std::map<std::string, SunScripting::SunLuaTypeDataMemberBase<SunObject> *> SunLuaTypeRegistrar<SunObject>::dataMembers = {
    {"rotation", new SunLuaComplexDataMember<glm::vec3, SunObject>("rotation", &SunObject::rotation)},
    {"position", new SunLuaComplexDataMember<glm::vec3, SunObject>("position", &SunObject::position)},
    {"scale", new SunLuaComplexDataMember<glm::vec3, SunObject>("scale", &SunObject::scale)}
};

SunObject::SunObject() : physicsEnabled(false) {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

SunObject::SunObject(std::string _name) : physicsEnabled(false) {
    setName(_name);
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

void SunObject::loadScript(std::string _script) {
    // Load the script
    scriptingEnabled = true;
    script.loadFile(_script);
    // Register the object
    script.registerType<glm::vec3>();
    script.registerType<SunObject>();
    script.registerObject(this, "object");
    /*for (auto &mesh : meshes) {
        const char *name = mesh.first.c_str();
        script.registerObject(script["object"][name], &mesh.second);
        script.registerObjectAsType(script["object"][name]["position"], "vec3", &mesh.second.position);
        script.registerObject(script["object"][name]["material"], mesh.second.material);
        script.registerObjectAsType(script["object"][name]["material"]["color"], "vec3", &mesh.second.material->diffuse);
    }*/
    ((SunKeyboardManager *)getService("keyboard_manager"))->registerWithScript(&script);
    ((SunGlobalScriptingEnvironment *)getService("global_logic_environment"))->registerWithScript(script);

    //script.registerObject("keyboard_manager", (SunKeyboardManager *)getService("keyboard_manager"), "pollKey", &SunKeyboardManager::keyDown);
}

void SunObject::registerInScript(SunScript *script, _SunPrivateScripting::SunLuaValue value) {
    /*script->registerObject(value, this);
    script->registerObjectAsType(value["rotation"], "vec3", &rotation);
    script->registerObjectAsType(value["position"], "vec3", &position);
    script->registerObjectAsType(value["scale"], "vec3", &scale);*/
}

void SunObject::registerInScript(SunAction action) {
    /*SunScript *script = action.getParameterPointer<SunScript>("script");
    _SunPrivateScripting::SunLuaValue value = action.getParameter<_SunPrivateScripting::SunLuaValue>("value");
    script->registerObject(value, this);
    script->registerObjectAsType(value["rotation"], "vec3", &rotation);
    script->registerObjectAsType(value["position"], "vec3", &position);
    script->registerObjectAsType(value["scale"], "vec3", &scale);*/
}

void SunObject::init() {
    addAction("update", &SunObject::update);
    addAction("render", &SunObject::render);
    addAction("playSound", &SunObject::playSound);
    addAction("uniform", &SunObject::uniform);
    addAction("registerInScript", &SunObject::registerInScript);
    ((SunGlobalScriptingEnvironment *)getService("global_logic_environment"))->registerObject(this);
    if (scriptingEnabled == true)
        script["init"]();
}

void SunObject::update(SunAction action) {
    float delta = ((SunWindowManager *)getService("window_manager"))->getDelta();
    if (scriptingEnabled == true)
        script["update"](delta);
    if (physicsEnabled == true)
        position = physicsObject.getPosition();
}

void SunObject::render(SunAction action) {
    SunShader *shader = action.getParameterPointer<SunShader>("shader");
    for (auto &mesh : meshes)
        mesh.second.render(shader);
}

void SunObject::playSound(SunAction action) {
    SunAction soundAction("playSound");
    soundAction.addParameter("position", &position);

    sendAction(soundAction, &sound);
}

void SunObject::uniform(SunAction action) {

}

void SunObject::newMesh(std::string name, std::string mesh, std::string material) {
    SunMeshResource *_mesh = (SunMeshResource *)((SunResourceService *)getService("resource_service"))->getResourceManager("meshes")->getResource(mesh);

    SunMaterialResource *_material = (SunMaterialResource *)((SunResourceService *)getService("resource_service"))->getResourceManager("materials")->getResource(material);
    meshes[name] = SunMesh(this, _mesh, _material);
}

void SunObject::newMesh(std::string name, std::string mesh, std::string material, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale) {
    SunMeshResource *_mesh = (SunMeshResource *)((SunResourceService *)getService("resource_service"))->getResourceManager("meshes")->getResource(mesh);

    SunMaterialResource *_material = (SunMaterialResource *)((SunResourceService *)getService("resource_service"))->getResourceManager("materials")->getResource(material);
    meshes[name] = SunMesh(this, _mesh, _material, _position, _rotation, _scale);
}
