// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunDirectionalLight.h"

#include "../Graphics/SunShader.h"

SunDirectionalLight::SunDirectionalLight() {

}

SunDirectionalLight::SunDirectionalLight(glm::vec3 _color, glm::vec3 _direction) : color(_color), direction(_direction) {

}

void SunDirectionalLight::init() {
    addAction("update", &SunDirectionalLight::update);
    addAction("uniform", &SunDirectionalLight::uniform);
}

void SunDirectionalLight::update(SunAction action) {

}


void SunDirectionalLight::uniform(SunAction action) {
    SunShader *shader = action.getParameterPointer<SunShader>("shader");
    int id = shader->getNextArrayIndex("directionalLights");
    glUniform3f(shader->getUniformLocation("directionalLights[" + std::to_string(id) + "].color"), color.r, color.g, color.b);

    glUniform3f(shader->getUniformLocation("directionalLights[" + std::to_string(id) + "].direction"), direction.x, direction.y, direction.z);

    glUniform1i(shader->getUniformLocation("directionalLightCount"), shader->getArraySize("directionalLights"));
}
