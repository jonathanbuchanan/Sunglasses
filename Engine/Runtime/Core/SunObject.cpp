// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunObject.h"
#include "Graphics/SunWindowManager.h"

SunObject::SunObject() {
    init();
}

SunObject::SunObject(string _name, string _modelPath, bool _flipNormals) {
	setName(_name);
    setFlipNormals(_flipNormals);

    init();

    SunModel model = SunModel(_modelPath, flipNormals);
    models.push_back(model);
}

SunObject::SunObject(string _name, string _modelPath, string tag, bool _flipNormals) {
	setName(_name);
	setFlipNormals(_flipNormals);
	addTag(tag);
	init();

<<<<<<< HEAD
    // Map position, rotation, and scale to the property map
    //addToPropertyMap("position", SunNodeProperty(&position, SunNodePropertyTypeVec3));
    //addToPropertyMap("rotation", SunNodeProperty(&rotation, SunNodePropertyTypeVec3));
    //addToPropertyMap("scale", SunNodeProperty(&scale, SunNodePropertyTypeVec3));
    //addToPropertyMap("renderType", SunNodeProperty(&renderType, SunNodePropertyTypeInt));
=======
	SunModel model = SunModel(_modelPath, flipNormals);
	models.push_back(model);
}
>>>>>>> render

void SunObject::init() { 
	addAction("update", &SunObject::update);
	addAction("render", &SunObject::render);
<<<<<<< HEAD
	addAction("playSound", &SunObject::playSound); 
    //addToFunctionMap("passPerFrameUniforms", bind(&SunObject::passPerFrameUniforms, this, std::placeholders::_1));
=======
	addAction("playSound", &SunObject::playSound);
	addAction("uniform", &SunObject::uniform); 
>>>>>>> render
}

void SunObject::update(SunAction action) {
    if (physicsEnabled == true)
        position = physicsObject.getPosition();
}

void SunObject::render(SunAction action) {
	SunShader shader = *(SunShader *)action.getParameter("shader");
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
