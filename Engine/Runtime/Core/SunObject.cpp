// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunObject.h"

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

void SunObject::init() { 
    //setType("object");

    // Map position, rotation, and scale to the property map 

    // Add the "render" function to the function map
	addAction("update", &SunObject::update);
	addAction("render", &SunObject::render);
	addAction("playSound", &SunObject::playSound);
	addAction("passPerFrameUniforms", &SunObject::passPerFrameUniforms); 
}

void SunObject::update(SunAction action) {
    if (physicsEnabled == true)
        position = physicsObject.getPosition();
}

void SunObject::render(SunAction action) {
    if (action.parameterExists("renderType")) {
        if (renderType == *(int *)action.getParameter("renderType") || *(int *)action.getParameter("renderType") == SunMeshRenderTypeAll) {
            SunShader _shader = *(SunShader *)action.getParameter("shader");
            GLfloat _deltaTime = *(GLfloat *)action.getParameter("deltaTime");
            
            SunMeshRenderType _renderType = (SunMeshRenderType)(*(int *)action.getParameter("renderType"));
                        
            // Loop through the models and render them
            for (int i = 0; i < models.size(); ++i) {
                models[i].render(_shader, _deltaTime, position, rotation, scale, material, _renderType);
            }
        }
    } else {
        SunShader _shader = *(SunShader *)action.getParameter("shader");
        GLfloat _deltaTime = *(GLfloat *)action.getParameter("deltaTime");

        // Loop through the models and render them
        for (int i = 0; i < models.size(); ++i) {
            models[i].render(_shader, _deltaTime, position, rotation, scale, material, renderType);
        }
    }
}

void SunObject::playSound(SunAction action) {
	SunAction soundAction("playSound");
	soundAction.addParameter("position", &position);

    sendAction(soundAction, &sound);
}

void SunObject::passPerFrameUniforms(SunAction action) {
    
}

void SunObject::passPOVUniforms(SunShader _shader) {
    
}
