// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/SunGUIRenderer.h>

#include <sunglasses/GUI/SunGUIWindow.h>

#include <string>

#include <glm/gtx/string_cast.hpp>

const std::string fill_vertex = R"(
#version 330 core

layout (location = 0) in ivec2 vertex;
// TexCoords

uniform mat4 model;
uniform mat4 projection;

void main() {
    gl_Position = projection * model * vec4(vertex, 0.0f, 1.0f);
}
)";

GLuint __indices[] = {
    0, 1, 2,
    1, 2, 3
};

const std::string fill_fragment = R"(
#version 330 core

out vec4 color;

uniform vec4 fillColor;

void main() {
    color = fillColor;
}
)";

SunGUIRenderer::SunGUIRenderer(SunGUIWindow &_window) :
    window(_window), fillShader(fill_vertex, fill_fragment) {

}

void SunGUIRenderer::drawRect(const SunGUIRect &rect, glm::vec4 color) {
    fillShader.use();
    // TODO: Add color
    rect.draw(fillShader, window.projection(), color);
}
