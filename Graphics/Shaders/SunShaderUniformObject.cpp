#include "SunShaderUniformObject.h"

void SunShaderUniformObject::initializeDefaultPropertyAndFunctionMap() {
    SunNode::initializeDefaultPropertyAndFunctionMap();

    addToFunctionMap("passUniform", bind(&SunShaderUniformObject::passUniform, this, placeholders::_1));
}

void SunShaderUniformObject::passUniform(SunNodeSentAction _action) {
    SunShader shader = *(SunShader *) _action.parameters["shader"];
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

void SunShaderHemisphereKernelObject::passUniform(SunNodeSentAction _action) {
    SunShader shader = *(SunShader *) _action.parameters["shader"];

    for (int i = 0; i < sampleCount; i++) {
        GLint location = shader.getUniformLocation(getUniformName() + "[" + to_string(i) + "]");
        glUniform3f(location, samples[i].x, samples[i].y, samples[i].z);
    }
}