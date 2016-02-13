// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunShaderUniformObject.h"

void SunShaderUniformObject::initializeDefaultPropertyAndFunctionMap() {
    //SunNode::initializeDefaultPropertyAndFunctionMap();

	addAction("passUniform", &SunShaderUniformObject::passUniformAction);
}

void SunShaderUniformObject::passUniformAction(SunAction action) {
    SunShader shader = *(SunShader *)action.getParameter("shader");
    
    switch (type) {
    	case SunShaderUniformObjectTypeMatrix4x4:
    		glUniformMatrix4fv(shader.getUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(*(glm::mat4 *)value));
    		break;
    	case SunShaderUniformObjectTypeFloat:
    		glUniform1f(shader.getUniformLocation(uniformName), *(GLfloat *)value);
    		break;
    	case SunShaderUniformObjectTypeInteger:
    		glUniform1i(shader.getUniformLocation(uniformName), *(GLuint *)value);
    		break;
    	case SunShaderUniformObjectTypeVec3:
    		glUniform3fv(shader.getUniformLocation(uniformName), 1, glm::value_ptr(*(glm::vec3 *)value));
    		break;
    }
}

void SunShaderUniformObject::passUniform(SunShader *_shader) {
    switch (type) {
    	case SunShaderUniformObjectTypeMatrix4x4:
    		glUniformMatrix4fv(_shader->getUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(*(glm::mat4 *)value));
    		break;
    	case SunShaderUniformObjectTypeFloat:
    		glUniform1f(_shader->getUniformLocation(uniformName), *(GLfloat *)value);
    		break;
    	case SunShaderUniformObjectTypeInteger:
    		glUniform1i(_shader->getUniformLocation(uniformName), *(GLuint *)value);
    		break;
    	case SunShaderUniformObjectTypeVec3:
    		glUniform3fv(_shader->getUniformLocation(uniformName), 1, glm::value_ptr(*(glm::vec3 *)value));
    		break;
    }
}



SunShaderHemisphereKernelObject::SunShaderHemisphereKernelObject(int _sampleCount) {
    initializeDefaultPropertyAndFunctionMap();
    sampleCount = _sampleCount;
    generate(_sampleCount);
}

void SunShaderHemisphereKernelObject::generate(int _sampleCount) {
    for (int i = 0; i < _sampleCount; i++) {
        glm::vec3 sample = glm::vec3(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
        sample = glm::normalize(sample);
        sample *= randomFloats(generator);
        GLfloat scale = GLfloat(i) / 64.0f;
        scale = glm::lerp(0.1f, 1.0f, scale * scale);
        sample *= scale;
        samples.push_back(sample);
    }
}

void SunShaderHemisphereKernelObject::passUniform(SunAction action) {
    SunShader shader = *(SunShader *)action.getParameter("shader");

    for (int i = 0; i < sampleCount; i++) {
        GLint location = shader.getUniformLocation(getUniformName() + "[" + to_string(i) + "]");
        glUniform3f(location, samples[i].x, samples[i].y, samples[i].z);
    }
}
