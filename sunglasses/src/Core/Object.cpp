// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Core/Object.h>

#include <sunglasses/Graphics/WindowManager.h>
#include <sunglasses/Graphics/Loaders/MaterialResource.h>
#include <sunglasses/Input/KeyboardManager.h>
#include <sunglasses/Scripting/GlobalScriptingEnvironment.h>
#include <sunglasses/Extern/ResourceService.h>

namespace sunglasses {

template<> const std::string LuaTypeRegistrar<Object>::typeName = "Object";
template<> const std::map<std::string, Scripting::LuaTypeDataMemberBase<Object> *> LuaTypeRegistrar<Object>::dataMembers = {
    {"rotation", new LuaComplexDataMember<glm::vec3, Object>("rotation", &Object::rotation)},
    {"position", new LuaComplexDataMember<glm::vec3, Object>("position", &Object::position)},
    {"scale", new LuaComplexDataMember<glm::vec3, Object>("scale", &Object::scale)}
};

Object::Object() : physicsEnabled(false) {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Object::Object(std::string _name) : physicsEnabled(false) {
    setName(_name);
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Object::loadScript(std::string _script) {
    // Load the script
    scriptingEnabled = true;
    script.loadFile(_script);
    // Register the object
    script.registerType<glm::vec3>();
    script.registerType<Object>();
    script.registerObject(this, "object");
    /*for (auto &mesh : meshes) {
        const char *name = mesh.first.c_str();
        script.registerObject(script["object"][name], &mesh.second);
        script.registerObjectAsType(script["object"][name]["position"], "vec3", &mesh.second.position);
        script.registerObject(script["object"][name]["material"], mesh.second.material);
        script.registerObjectAsType(script["object"][name]["material"]["color"], "vec3", &mesh.second.material->diffuse);
    }*/
    services.get<GlobalScriptingEnvironment>()->registerScript(this, script); 
}

void Object::registerInScript(Script *script, _PrivateScripting::LuaValue value) {
    /*script->registerObject(value, this);
    script->registerObjectAsType(value["rotation"], "vec3", &rotation);
    script->registerObjectAsType(value["position"], "vec3", &position);
    script->registerObjectAsType(value["scale"], "vec3", &scale);*/
}

void Object::registerInScript(Action action) {
    /*Script *script = action.getParameterPointer<Script>("script");
    _PrivateScripting::LuaValue value = action.getParameter<_PrivateScripting::LuaValue>("value");
    script->registerObject(value, this);
    script->registerObjectAsType(value["rotation"], "vec3", &rotation);
    script->registerObjectAsType(value["position"], "vec3", &position);
    script->registerObjectAsType(value["scale"], "vec3", &scale);*/
}

void Object::init() {
    addAction("update", &Object::update);
    addAction("render", &Object::render);
    addAction("uniform", &Object::uniform);
    addAction("registerInScript", &Object::registerInScript);
    services.get<GlobalScriptingEnvironment>()->registerObject(this);
    if (scriptingEnabled == true)
        script["init"]();
}

void Object::update(Action action) {
    float delta = services.get<WindowManager>()->getDelta();
    if (scriptingEnabled == true)
        script["update"](delta);
    if (physicsEnabled == true)
        position = physicsObject.getPosition();
}

void Object::render(Action action) {
    Shader *shader = action.getParameterPointer<Shader>("shader");
    for (auto &mesh : meshes)
        mesh.second.render(shader);
}

void Object::uniform(Action action) {

}

void Object::newMesh(std::string name, std::string mesh, std::string material) {
    MeshResource *_mesh = (MeshResource *)services.get<ResourceService>()->getResourceManager("meshes")->getResource(mesh);

    MaterialResource *_material = (MaterialResource *)services.get<ResourceService>()->getResourceManager("materials")->getResource(material);
    meshes[name] = Mesh(this, _mesh, _material);
}

void Object::newMesh(std::string name, std::string mesh, std::string material, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale) {
    MeshResource *_mesh = (MeshResource *)services.get<ResourceService>()->getResourceManager("meshes")->getResource(mesh);

    MaterialResource *_material = (MaterialResource *)services.get<ResourceService>()->getResourceManager("materials")->getResource(material);
    meshes[name] = Mesh(this, _mesh, _material, _position, _rotation, _scale);
}

void Object::newAudioSource(std::string name, std::string buffer,
        glm::vec3 position, float pitch, float gain) {
    AudioBufferResource *_buffer = (AudioBufferResource *)services.get<ResourceService>()->getResourceManager("sounds")->getResource(buffer);

    audioSources.emplace(std::make_pair(name, AudioSource(_buffer, position, pitch, gain)));
}

void Object::playAudioSource(std::string name) {
    audioSources.at(name).play();
}

} // sunglasses
