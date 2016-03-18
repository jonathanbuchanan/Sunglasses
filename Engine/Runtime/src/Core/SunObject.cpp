// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunObject.h"
#include "../Graphics/SunWindowManager.h"
#include "../Input/SunKeyboardManager.h"
#include "../Logic/SunGlobalLogicEnvironment.h"

SunObject::SunObject() : physicsEnabled(false) {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    flipNormals = false;
}

SunObject::SunObject(string _name, string _modelPath, bool _flipNormals) : flipNormals(_flipNormals), physicsEnabled(false) {
    SunObject();
	setName(_name);

    model = SunModel(_modelPath, flipNormals);
}

SunObject::SunObject(string _name, string _modelPath, string tag, bool _flipNormals) : flipNormals(_flipNormals), physicsEnabled(false) {
    SunObject();
	setName(_name);
	addTag(tag);

	model = SunModel(_modelPath, flipNormals);
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
    script.registerObjectAsType(script["object"]["color"], "vec3", &material.color);
    ((SunGlobalLogicEnvironment *)getService("global_logic_environment"))->registerWithScript(&script);

    script.registerObject("keyboard_manager", (SunKeyboardManager *)getService("keyboard_manager"), "pollKey", &SunKeyboardManager::keyDown);
}

void SunObject::init() {
	addAction("update", &SunObject::update);
	addAction("render", &SunObject::render);
	addAction("playSound", &SunObject::playSound);
	addAction("uniform", &SunObject::uniform);
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
	SunShader shader = action.getParameter<SunShader>("shader");
	GLfloat delta = ((SunWindowManager *)getService("window_manager"))->getDelta();
	model.render(shader, delta, position, rotation, scale, material, SunMeshRenderTypeAll);
}

void SunObject::playSound(SunAction action) {
	SunAction soundAction("playSound");
	soundAction.addParameter("position", &position);

    sendAction(soundAction, &sound);
}

void SunObject::uniform(SunAction action) {

}

void SunObject::passPOVUniforms(SunShader _shader) {

}
