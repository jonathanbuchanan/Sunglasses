// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Extra/PointLight.h>

#include <sunglasses/Graphics/Shader.h>

namespace sunglasses {

PointLight::PointLight() {

}

PointLight::PointLight(glm::vec3 _color, glm::vec3 _position) : color(_color), position(_position) {

}

void PointLight::init() {
    addAction("update", &PointLight::update);
    addAction("uniform", &PointLight::uniform);
}

void PointLight::update(Action action) {

}

void PointLight::uniform(Action action) {
    Shader *shader = action.getParameterPointer<Shader>("shader");
    int id = shader->getNextArrayIndex("pointLights");

    (*shader)["pointLights[" + std::to_string(id) + "].color"] = color;

    (*shader)["pointLights[" + std::to_string(id) + "].position"] = position;

    (*shader)["pointLights[" + std::to_string(id) + "].attenuate"] = true;

    (*shader)["pointLightCount"] = shader->getArraySize("pointLights");
}

} // namespace
