// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunObject.h"
#include "../Graphics/SunWindowManager.h"

SunObject::SunObject() {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    physicsEnabled = false;
    flipNormals = false;
}

SunObject::SunObject(string _name, string _modelPath, bool _flipNormals) : flipNormals(_flipNormals) {
    SunObject();
	setName(_name);

    SunModel model = SunModel(_modelPath, flipNormals);
    models.push_back(model);
}

SunObject::SunObject(string _name, string _modelPath, string tag, bool _flipNormals) : flipNormals(_flipNormals) {
    SunObject();
	setName(_name);
	addTag(tag);

	SunModel model = SunModel(_modelPath, flipNormals);
	models.push_back(model);
}

void SunObject::init() {
	addAction("update", &SunObject::update);
	addAction("render", &SunObject::render);
	addAction("playSound", &SunObject::playSound);
	addAction("uniform", &SunObject::uniform);
}

void SunObject::update(SunAction action) {
    if (physicsEnabled == true)
        position = physicsObject.getPosition();
}

void SunObject::render(SunAction action) {
	SunShader shader = action.getParameter<SunShader>("shader");
	GLfloat delta = ((SunWindowManager *)getService("window_manager"))->getDelta();
	for (int i = 0; i < models.size(); ++i)
		models[i].render(shader, delta, position, rotation, scale, material, SunMeshRenderTypeAll);
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
