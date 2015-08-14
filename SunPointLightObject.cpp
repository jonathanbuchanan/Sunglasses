#include "SunPointLightObject.h"

SunPointLightObject::SunPointLightObject() {
    initializeDefaultPropertyAndFunctionMap();
}

SunPointLightObject::SunPointLightObject(glm::vec3 _color, glm::vec3 _position) {
    color = _color;
    position = _position;
    
    initializeDefaultPropertyAndFunctionMap();
}

SunPointLightObject::SunPointLightObject(string _name) {
    setName(_name);

    initializeDefaultPropertyAndFunctionMap();
}

void SunPointLightObject::initializeDefaultPropertyAndFunctionMap() {
    SunObject::initializeDefaultPropertyAndFunctionMap();

    setType("light");
}

void SunPointLightObject::passPerFrameUniforms(SunNodeSentAction _action) {
    SunObject::passPerFrameUniforms(_action);

    SunShader _shader = *(SunShader *) _action.parameters["shader"];

    // Set the uniforms for the point light's diffuse and specular colors
    glUniform3f(_shader.getUniformLocation("pointLight.color"), color.r, color.g, color.b);

    // Set the uniform for the point light's position
    glUniform3f(_shader.getUniformLocation("pointLight.position"), position.x, position.y, position.z);

    // Set the uniforms for the point light's constant, linear, and quadratic terms
    glUniform1i(_shader.getUniformLocation("pointLight.attenuate"), attenuate);
}