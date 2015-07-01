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

#include "SunModel.h"

#include "glm/gtx/string_cast.hpp"

typedef void * PropertyPointer;

enum SunObjectPropertyType {
    SunObjectPropertyTypeBool,
    SunObjectPropertyTypeInt,
    SunObjectPropertyTypeFloat,
    SunObjectPropertyTypeVec2,
    SunObjectPropertyTypeVec3
};

struct SunObjectProperty {
    PropertyPointer pointer;
    SunObjectPropertyType type;
    
    SunObjectProperty() {
        
    }
    
    SunObjectProperty(PropertyPointer _pointer, SunObjectPropertyType _type) {
        pointer = _pointer;
        type = _type;
    }
    
};

class SunObject {
public:
    // Tag and name
    int tag;
    string name;
    
    // Super-object and sub-objects
    SunObject *superObject;
    vector<SunObject *> subObjects;
    
    // Object position and rotation
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    
    // Sub-models
    vector<SunModel> models;
    
    // Properties
    map<string, SunObjectProperty> properties;
    SunObjectMaterial material;
    
    SunObject() {
        initializeDefaultPropertyMap();
    }
    
    SunObject(SunObject *_superObject, int _tag) {
        superObject = _superObject;
        tag = _tag;
        
        initializeDefaultPropertyMap();
        
        superObject->addSubObject(this);
    }
    
    SunObject(SunObject *_superObject, int _tag, string _name) {
        superObject = _superObject;
        tag = _tag;
        name = _name;
        
        initializeDefaultPropertyMap();
        
        superObject->addSubObject(this);
    }
    
    SunObject(SunObject *_superObject, int _tag, string _name, string _modelPath) {
        superObject = _superObject;
        tag = _tag;
        name = _name;
        
        initializeDefaultPropertyMap();
        
        superObject->addSubObject(this);
        
        SunModel model = SunModel(_modelPath);
        models.push_back(model);
    }
    
    SunObject(int _tag, string _name, string _modelPath) {
        tag = _tag;
        name = _name;
        
        initializeDefaultPropertyMap();
        
        SunModel model = SunModel(_modelPath);
        models.push_back(model);
    }
    
    void initializeDefaultPropertyMap() {
        properties["position"] = SunObjectProperty(&position, SunObjectPropertyTypeVec3);
        properties["rotation"] = SunObjectProperty(&rotation, SunObjectPropertyTypeVec3);
        properties["scale"] = SunObjectProperty(&scale, SunObjectPropertyTypeVec3);
    }
    
    virtual void addSubObject(SunObject *_subObject) {
        // Add the sub-object and set the sub-object's super-object to this object
        subObjects.push_back(_subObject);
        _subObject->superObject = this;
    }
    
    virtual void update() {
        // Loop through the sub-objects and force them to update
        for (int i = 0; i < subObjects.size(); ++i) {
            subObjects[i]->update();
        }
    }
    
    virtual void render(SunShader _shader, GLfloat _deltaTime) {
        // Loop through the models and render them
        for (int i = 0; i < models.size(); ++i) {
            models[i].render(_shader, _deltaTime, position, rotation, scale, material);
        }
        
        // Loop through the sub-objects and force them to render
        for (int i = 0; i < subObjects.size(); ++i) {
            subObjects[i]->render(_shader, _deltaTime);
        }
    }
    
    virtual void passPerFrameUniforms(SunShader _shader) {
        // Loop through the sub-objects and force them to pass their uniforms
        for (int i = 0; i < subObjects.size(); ++i) {
            subObjects[i]->passPerFrameUniforms(_shader);
        }
    }
private:
    
};

#endif
