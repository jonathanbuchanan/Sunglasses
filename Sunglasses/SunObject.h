//
//  Object.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/12/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_Object_h
#define OpenGL_Test_3_Object_h

#include <vector>
using namespace std;

#include "SunNode.h"

#include "SunModel.h"

#include "glm/gtx/string_cast.hpp"

class SunObject : public SunNode {
public:
    // Tag and name
    int tag;
    string name;
    
    // Object position and rotation
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    
    // Sub-models
    vector<SunModel> models;
    
    SunObjectMaterial material;
    
    SunObject() {
        initializeDefaultPropertyAndFunctionMap();
    }
    
    SunObject(int _tag) {
        tag = _tag;
        
        initializeDefaultPropertyAndFunctionMap();
    }
    
    SunObject(int _tag, string _name) {
        tag = _tag;
        name = _name;
        
        initializeDefaultPropertyAndFunctionMap();
    }
    
    SunObject(int _tag, string _name, string _modelPath) {
        tag = _tag;
        name = _name;
        
        initializeDefaultPropertyAndFunctionMap();
        
        SunModel model = SunModel(_modelPath);
        models.push_back(model);
    }
    
    virtual void initializeDefaultPropertyAndFunctionMap() {
        // Map position, rotation, and scale to the property map
        propertyMap["position"] = SunNodeProperty(&position, SunNodePropertyTypeVec3);
        propertyMap["rotation"] = SunNodeProperty(&rotation, SunNodePropertyTypeVec3);
        propertyMap["scale"] = SunNodeProperty(&scale, SunNodePropertyTypeVec3);
        
        // Add the "render" function to the function map
        functionMap["render"] = bind(&SunObject::render, this, std::placeholders::_1);
        functionMap["passPerFrameUniforms"] = bind(&SunObject::passPerFrameUniforms, this, std::placeholders::_1);
    }
    
    /*virtual void update() {
        // Loop through the sub-objects and force them to update
        for (int i = 0; i < subObjects.size(); ++i) {
            subObjects[i]->update();
        }
    }*/
    
    virtual void render(SunNodeSentAction _action) {
        SunShader _shader = *(SunShader *)_action.parameters["shader"];
        GLfloat _deltaTime = *(GLfloat *)_action.parameters["deltaTime"];
        
        // Loop through the models and render them
        for (int i = 0; i < models.size(); ++i) {
            models[i].render(_shader, _deltaTime, position, rotation, scale, material);
        }
        
        // Loop through the sub-objects and force them to render
        for (int i = 0; i < subNodes.size(); ++i) {
            sendAction(_action, subNodes[i]);
        }
    }
    
    virtual void passPerFrameUniforms(SunNodeSentAction _action) {
        SunShader _shader = *(SunShader *)_action.parameters["shader"];
        
        for (int i = 0; i < subNodes.size(); ++i) {
            sendAction(_action, subNodes[i]);
        }
    }
    
private:
    
};

#endif
