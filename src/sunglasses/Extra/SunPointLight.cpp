// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunPointLight.h"

#include "../Graphics/SunShader.h"

SunPointLight::SunPointLight() {

}

SunPointLight::SunPointLight(glm::vec3 _color, glm::vec3 _position) : color(_color), position(_position) {

}

void SunPointLight::init() {
    addAction("update", &SunPointLight::update);
    addAction("uniform", &SunPointLight::uniform);
}

void SunPointLight::update(SunAction action) {

}

void SunPointLight::uniform(SunAction action) {
    SunShader *shader = action.getParameterPointer<SunShader>("shader");
    int id = shader->getNextArrayIndex("pointLights");

    glUniform3f(shader->getUniformLocation("pointLights[" + std::to_string(id) + "].color"), color.r, color.g, color.b);

    glUniform3f(shader->getUniformLocation("pointLights[" + std::to_string(id) + "].position"), position.x, position.y, position.z);

    glUniform1i(shader->getUniformLocation("pointLights[" + std::to_string(id) + "].attenuate"), true);

    glUniform1i(shader->getUniformLocation("pointLightCount"), shader->getArraySize("pointLights"));
}
