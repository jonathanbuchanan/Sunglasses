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

#include "./SunNode.h"

#include "./Graphics/SunModel.h"

#include "./Libraries/glm/gtx/string_cast.hpp"
#include "Utility.h"

class SunObject : public SunNode {
public:
    // Object position and rotation
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    
    // Sub-models
    vector<SunModel> models;
    
    SunObjectMaterial material;
    SunMeshRenderType renderType;
    
    SunObject() {
        initializeDefaultPropertyAndFunctionMap();
    }
    
    SunObject(string _name, string _modelPath) {
        name = _name;
        
        initializeDefaultPropertyAndFunctionMap();
        
        SunModel model = SunModel(_modelPath);
        models.push_back(model);
    }
    
    virtual void initializeDefaultPropertyAndFunctionMap() {
        SunNode::initializeDefaultPropertyAndFunctionMap();
        
        // Map position, rotation, and scale to the property map
        propertyMap["position"] = SunNodeProperty(&position, SunNodePropertyTypeVec3);
        propertyMap["rotation"] = SunNodeProperty(&rotation, SunNodePropertyTypeVec3);
        propertyMap["scale"] = SunNodeProperty(&scale, SunNodePropertyTypeVec3);
        
        // Add the "render" function to the function map
        functionMap["update"] = bind(&SunObject::update, this, std::placeholders::_1);
        functionMap["render"] = bind(&SunObject::render, this, std::placeholders::_1);
        functionMap["passPerFrameUniforms"] = bind(&SunObject::passPerFrameUniforms, this, std::placeholders::_1);
    }
    
    virtual void update(SunNodeSentAction _action) {
        // Loop through the sub-objects and force them to update
        for (int i = 0; i < subNodes.size(); ++i) {
            sendAction(_action, subNodes[i]);
        }
    }
    
    virtual void render(SunNodeSentAction _action) {
        if (_action.parameters.find("renderType") != _action.parameters.end()) {
            if (renderType == *(int *)_action.parameters["renderType"]) {
                SunShader _shader = *(SunShader *)_action.parameters["shader"];
                GLfloat _deltaTime = *(GLfloat *)_action.parameters["deltaTime"];
                
                // Loop through the models and render them
                for (int i = 0; i < models.size(); ++i) {
                    models[i].render(_shader, _deltaTime, position, rotation, scale, material, renderType);
                }
            }
        } else {
            SunShader _shader = *(SunShader *)_action.parameters["shader"];
            GLfloat _deltaTime = *(GLfloat *)_action.parameters["deltaTime"];
            
            // Loop through the models and render them
            for (int i = 0; i < models.size(); ++i) {
                models[i].render(_shader, _deltaTime, position, rotation, scale, material, renderType);
            }
        }
        
        // Loop through the sub-objects and force them to render
        sendActionToAllSubNodes(_action);
    }
    
    virtual void passPerFrameUniforms(SunNodeSentAction _action) {
        sendActionToAllSubNodes(_action);
    }
    
private:
    
};

#endif
