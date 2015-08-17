#include "SunObject.h"

SunObject::SunObject() {
    initializeDefaultPropertyAndFunctionMap();
}

SunObject::SunObject(string _name, string _modelPath) {
    setName(_name);

    initializeDefaultPropertyAndFunctionMap();

    SunModel model = SunModel(_modelPath);
    models.push_back(model);
}

void SunObject::initializeDefaultPropertyAndFunctionMap() {
    SunNode::initializeDefaultPropertyAndFunctionMap();

    setType("object");

    // Map position, rotation, and scale to the property map
    addToPropertyMap("position", SunNodeProperty(&position, SunNodePropertyTypeVec3));
    addToPropertyMap("rotation", SunNodeProperty(&rotation, SunNodePropertyTypeVec3));
    addToPropertyMap("scale", SunNodeProperty(&scale, SunNodePropertyTypeVec3));
    addToPropertyMap("renderType", SunNodeProperty(&renderType, SunNodePropertyTypeInt));

    // Add the "render" function to the function map
    addToFunctionMap("update", bind(&SunObject::update, this, std::placeholders::_1));
    addToFunctionMap("render", bind(&SunObject::render, this, std::placeholders::_1));
    addToFunctionMap("playSound", bind(&SunObject::playSound, this, std::placeholders::_1));
    addToFunctionMap("passPerFrameUniforms", bind(&SunObject::passPerFrameUniforms, this, std::placeholders::_1));
}

void SunObject::update(SunNodeSentAction _action) {
    if (physicsEnabled == true)
        position = physicsObject.getPosition();
}

void SunObject::render(SunNodeSentAction _action) {
    if (_action.parameters.find("renderType") != _action.parameters.end()) {
        if (renderType == *(int *) _action.parameters["renderType"]) {
            SunShader _shader = *(SunShader *) _action.parameters["shader"];
            GLfloat _deltaTime = *(GLfloat *) _action.parameters["deltaTime"];

            // Loop through the models and render them
            for (int i = 0; i < models.size(); ++i) {
                models[i].render(_shader, _deltaTime, position, rotation, scale, material, renderType);
            }
        }
    } else {
        SunShader _shader = *(SunShader *) _action.parameters["shader"];
        GLfloat _deltaTime = *(GLfloat *) _action.parameters["deltaTime"];

        // Loop through the models and render them
        for (int i = 0; i < models.size(); ++i) {
            models[i].render(_shader, _deltaTime, position, rotation, scale, material, renderType);
        }
    }
}

void SunObject::playSound(SunNodeSentAction _action) {
    _action.parameters["position"] = &position;
    sendAction(_action, &sound);
}

void SunObject::passPerFrameUniforms(SunNodeSentAction _action) {
    
}