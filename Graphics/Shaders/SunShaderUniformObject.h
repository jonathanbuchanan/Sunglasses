/* 
 * File:   SunShaderUniformObject.h
 * Author: jonathan
 *
 * Created on July 28, 2015, 9:27 PM
 */

#include "../../SunNode.h"
#include "./SunShader.h"
#include "../SunPrimitives.h"
#include "../../Libraries/glm/gtx/compatibility.hpp"

#ifndef SUNSHADERUNIFORMOBJECT_H
#define	SUNSHADERUNIFORMOBJECT_H

class SunShaderUniformObject : public SunNode {
public:
    SunShaderUniformObject() { initializeDefaultPropertyAndFunctionMap(); }
    
    virtual void initializeDefaultPropertyAndFunctionMap();
    
    virtual void passUniform(SunNodeSentAction _action);
    
    inline string getUniformName() { return uniformName; }
    inline void setUniformName(string _uniformName) { uniformName = _uniformName; }
private:
    string uniformName;
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

