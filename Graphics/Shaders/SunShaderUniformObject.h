/* 
 * File:   SunShaderUniformObject.h
 * Author: jonathan
 *
 * Created on July 28, 2015, 9:27 PM
 */

#include "../../SunNode.h"
#include "./SunShader.h"
#include "../SunPrimitives.h"

#ifndef SUNSHADERUNIFORMOBJECT_H
#define	SUNSHADERUNIFORMOBJECT_H

class SunShaderUniformObject : public SunNode {
public:
    string uniformName;
    
    SunShaderUniformObject() {
        initializeDefaultPropertyAndFunctionMap();
    }
    
    virtual void initializeDefaultPropertyAndFunctionMap() {
        SunNode::initializeDefaultPropertyAndFunctionMap();
        
        addToFunctionMap("passUniform", bind(&SunShaderUniformObject::passUniform, this, placeholders::_1));
    }
    
    virtual void passUniform(SunNodeSentAction _action) {
        SunShader shader = *(SunShader *)_action.parameters["shader"];
    }
    
private:
    
};

GLfloat lerp(GLfloat _a, GLfloat _b, GLfloat _t) {
    return _a + _t * (_b - _a);
}

class SunShaderHemisphereKernelObject : public SunShaderUniformObject {
public:
    vector<glm::vec3> samples;
    int sampleCount;
    
    SunShaderHemisphereKernelObject() {
        initializeDefaultPropertyAndFunctionMap();
    }
    
    SunShaderHemisphereKernelObject(int _sampleCount) {
        initializeDefaultPropertyAndFunctionMap();
        sampleCount = _sampleCount;
        generate(_sampleCount);
    }
    
    void generate(int _sampleCount) {
        for (int i = 0; i < _sampleCount; i++) {
            glm::vec3 sample = glm::vec3(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
            sample = glm::normalize(sample);
            sample *= randomFloats(generator);
            GLfloat scale = GLfloat(i) / 64.0f;
            scale = lerp(0.1f, 1.0f, scale * scale);
            sample *= scale;
            samples.push_back(sample);
        }
    }
    
    virtual void passUniform(SunNodeSentAction _action) {
        SunShader shader = *(SunShader *)_action.parameters["shader"];
        
        for (int i = 0; i < sampleCount; i++) {
            GLint location = shader.getUniformLocation(uniformName + "[" + to_string(i) + "]");
            glUniform3f(location, samples[i].x, samples[i].y, samples[i].z);
        }
    }
    
private:
    
};

#endif

