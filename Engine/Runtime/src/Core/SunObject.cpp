// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunObject.h"

#include "../Graphics/SunWindowManager.h"
#include "../Graphics/Loaders/SunMaterialResource.h"
#include "../Input/SunKeyboardManager.h"
#include "../Logic/SunGlobalLogicEnvironment.h"
#include "../Extern/SunResourceService.h"

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
    script.registerObject("object", this);
    script.registerType<glm::vec3>("vec3", "x", &glm::vec3::x, "y", &glm::vec3::y, "z", &glm::vec3::z);
    script.registerObjectAsType(script["object"]["rotation"], "vec3", &rotation);
    script.registerObjectAsType(script["object"]["position"], "vec3", &position);
    script.registerObjectAsType(script["object"]["scale"], "vec3", &scale);
    //script.registerObjectAsType(script["object"]["color"], "vec3", &material.color);
    //script.registerType<SunMesh>("mesh", "position")
    for (size_t i = 0; i < meshes.size(); i++) {
        const char *mesh = ("mesh" + std::to_string(i)).c_str();
        script.registerObject(script["object"][mesh], &meshes[i]);
        script.registerObjectAsType(script["object"][mesh]["position"], "vec3", &meshes[i].position);
        script.registerObject(script["object"][mesh]["material"], meshes[i].material);
        script.registerObjectAsType(script["object"][mesh]["material"]["color"], "vec3", &meshes[i].material->diffuse);
    }
    ((SunGlobalLogicEnvironment *)getService("global_logic_environment"))->registerWithScript(&script);

    script.registerObject("keyboard_manager", (SunKeyboardManager *)getService("keyboard_manager"), "pollKey", &SunKeyboardManager::keyDown);
}

void SunObject::init() {
	addAction("update", &SunObject::update);
	addAction("render", &SunObject::render);
	addAction("playSound", &SunObject::playSound);
	addAction("uniform", &SunObject::uniform);
    ((SunGlobalLogicEnvironment *)getService("global_logic_environment"))->registerObject(this);
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
	/*GLfloat delta = ((SunWindowManager *)getService("window_manager"))->getDelta();
	model.render(shader, delta, position, rotation, scale, material, SunMeshRenderTypeAll);*/
    for (size_t i = 0; i < meshes.size(); ++i)
        meshes[i].render(shader);
}

void SunObject::playSound(SunAction action) {
	SunAction soundAction("playSound");
	soundAction.addParameter("position", &position);

    sendAction(soundAction, &sound);
}

void SunObject::uniform(SunAction action) {

}

void SunObject::newMesh(std::string mesh, std::string material) {
    SunMeshResource *_mesh = (SunMeshResource *)((SunResourceService *)getService("resource_service"))->getResourceManager("meshes")->getResource(mesh);

    SunMaterialResource *_material = (SunMaterialResource *)((SunResourceService *)getService("resource_service"))->getResourceManager("materials")->getResource(material);
    meshes.push_back(SunMesh(this, _mesh, _material));
}

void SunObject::newMesh(std::string mesh, std::string material, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale) {
    SunMeshResource *_mesh = (SunMeshResource *)((SunResourceService *)getService("resource_service"))->getResourceManager("meshes")->getResource(mesh);

    SunMaterialResource *_material = (SunMaterialResource *)((SunResourceService *)getService("resource_service"))->getResourceManager("materials")->getResource(material);
    meshes.push_back(SunMesh(this, _mesh, _material, _position, _rotation, _scale));
}
