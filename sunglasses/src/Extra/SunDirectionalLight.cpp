// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Extra/SunDirectionalLight.h>

#include <sunglasses/Graphics/SunShader.h>

namespace sunglasses {

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
    (*shader)["directionalLights[" + std::to_string(id) + "].color"] = color;

    (*shader)["directionalLights[" + std::to_string(id) + "].color"] = direction;

    (*shader)["directionalLights[" + std::to_string(id) + "].color"] = shader->getArraySize("directionalLights");
}

} // namespace
