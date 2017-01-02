// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Extra/DirectionalLight.h>

#include <sunglasses/Graphics/Shader.h>

namespace sunglasses {

DirectionalLight::DirectionalLight() {

}

DirectionalLight::DirectionalLight(glm::vec3 _color, glm::vec3 _direction) : color(_color), direction(_direction) {

}

void DirectionalLight::init() {
    addAction("update", &DirectionalLight::update);
    addAction("uniform", &DirectionalLight::uniform);
}

void DirectionalLight::update(Action action) {

}


void DirectionalLight::uniform(Action action) {
    graphics::Shader *shader = action.getParameterPointer<graphics::Shader>("shader");
    int id = shader->getNextArrayIndex("directionalLights");
    (*shader)["directionalLights[" + std::to_string(id) + "].color"] = color;

    (*shader)["directionalLights[" + std::to_string(id) + "].color"] = direction;

    (*shader)["directionalLights[" + std::to_string(id) + "].color"] = shader->getArraySize("directionalLights");
}

} // namespace
