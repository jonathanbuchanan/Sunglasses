// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Extra/SunPointLight.h>

#include <sunglasses/Graphics/SunShader.h>

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

    (*shader)["pointLights[" + std::to_string(id) + "].color"] = color;

    (*shader)["pointLights[" + std::to_string(id) + "].position"] = position;

    (*shader)["pointLights[" + std::to_string(id) + "].attenuate"] = true;

    (*shader)["pointLightCount"] = shader->getArraySize("pointLights");
}