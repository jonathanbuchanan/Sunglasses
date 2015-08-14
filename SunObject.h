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
#include <functional>
#include "./Audio/SunSoundObject.h"

#include "./Graphics/SunModel.h"

#include "./Libraries/glm/gtx/string_cast.hpp"
#include "Utility.h"

class SunObject : public SunNode {
public:
    SunObject();
    SunObject(string _name, string _modelPath);
    
    virtual void initializeDefaultPropertyAndFunctionMap();
    virtual void update(SunNodeSentAction _action);
    virtual void render(SunNodeSentAction _action);
    virtual void playSound(SunNodeSentAction _action);
    virtual void passPerFrameUniforms(SunNodeSentAction _action);
    
    inline glm::vec3 & getPosition() { return position; }
    inline void setPosition(glm::vec3 _position) { position = _position; }
    inline void setPositionX(GLfloat x) { position.x = x; }
    inline void setPositionY(GLfloat y) { position.y = y; }
    inline void setPositionZ(GLfloat z) { position.z = z; }
    
    inline glm::vec3 & getRotation() { return rotation; }
    inline void setRotation(glm::vec3 _rotation) { rotation = _rotation; }
    inline void setRotationX(GLfloat x) { rotation.x = x; }
    inline void setRotationY(GLfloat y) { rotation.y = y; }
    inline void setRotationZ(GLfloat z) { rotation.z = z; }
    
    inline glm::vec3 & getScale() { return scale; }
    inline void setScale(glm::vec3 _scale) { scale = _scale; }
    inline void setScaleX(GLfloat x) { scale.x = x; }
    inline void setScaleY(GLfloat y) { scale.y = y; }
    inline void setScaleZ(GLfloat z) { scale.z = z; }
    
    inline SunSoundObject & getSoundObject() { return sound; }
    inline void setSoundObject(SunSoundObject _sound) { sound = _sound; }
    
    inline vector<SunModel> & getModels() { return models; }
    inline SunModel & getModelAtIndex(int i) { return models[i]; }
    inline void addModelToModels(SunModel model) { models.push_back(model); }
    
    inline SunObjectMaterial & getMaterial() { return material; }
    inline void setMaterial(SunObjectMaterial _material) { material = _material; }
    
    inline SunMeshRenderType & getRenderType() { return renderType; }
    inline void setRenderType(SunMeshRenderType _renderType) { renderType = _renderType; }
private:
    // Object position and rotation
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    
    // SunSoundObject
    SunSoundObject sound;
    
    // Sub-models
    vector<SunModel> models;
    
    SunObjectMaterial material;
    SunMeshRenderType renderType;
};

#endif
