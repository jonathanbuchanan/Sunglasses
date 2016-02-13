// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
/* 
 * File:   SunShaderUniformObject.h
 * Author: jonathan
 *
 * Created on July 28, 2015, 9:27 PM
 */

#include "SunNode.h"
#include "./SunShader.h"
#include "../SunPrimitives.h"
#include <glm/gtx/compatibility.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef SUNSHADERUNIFORMOBJECT_H
#define	SUNSHADERUNIFORMOBJECT_H

enum SunShaderUniformObjectType {
	SunShaderUniformObjectTypeMatrix4x4,
	SunShaderUniformObjectTypeVec3,
	SunShaderUniformObjectTypeFloat,
	SunShaderUniformObjectTypeInteger
};

typedef void * SunShaderUniformObjectValue;

class SunShaderUniformObject : public SunNode {
public:
    SunShaderUniformObject() { initializeDefaultPropertyAndFunctionMap(); }
    
    virtual void initializeDefaultPropertyAndFunctionMap();
    
    virtual void passUniformAction(SunAction action);
    virtual void passUniform(SunShader *_shader);
    
    inline string & getUniformName() { return uniformName; }
    inline void setUniformName(string _uniformName) { uniformName = _uniformName; }
    
    inline SunShaderUniformObjectType & getType() { return type; }
    inline void setType(SunShaderUniformObjectType t) { type = t; }
    
    inline SunShaderUniformObjectValue getValue() { return value; }
    inline void setValue(SunShaderUniformObjectValue v) { value = v; }
private:
    string uniformName;
    SunShaderUniformObjectType type;
    
    SunShaderUniformObjectValue value;
};

class SunShaderHemisphereKernelObject : public SunShaderUniformObject {
public:
    
    
    SunShaderHemisphereKernelObject() { initializeDefaultPropertyAndFunctionMap(); }
    
    SunShaderHemisphereKernelObject(int _sampleCount);
    
    virtual void generate(int _sampleCount);
    
    virtual void passUniform(SunNodeSentAction _action);
    
    inline vector<glm::vec3> & getSamples() { return samples; }
    inline void addToSamples(glm::vec3 _sample) { samples.push_back(_sample); }
    
    inline int & getSampleCount() { return sampleCount; }
    inline void setSampleCount(int _sampleCount) { sampleCount = _sampleCount; }
private:
    vector<glm::vec3> samples;
    int sampleCount;
};

#endif

