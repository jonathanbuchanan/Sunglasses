// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/SunGUIRendering.h>

#include <string>

const std::string fill_vertex = R"(
#version 330 core

layout (location = 0) in vec2 vertex;
// TexCoords

uniform model;
uniform projection;

void main() {
    gl_Position = projection * model * vec4(vertex, 0.0f, 1.0f);
}
)";

const std::string fill_fragment = R"(
#version 330

out vec4 color;

uniform vec3 fill;

void main() {
    color = vec4(fill, 1.0f);
}
)";

SunGUIShaderContainer::SunGUIShaderContainer(SunGUIWindow &window) :
    fill(fill_vertex, fill_fragment) {

}

SunGUIFillPath::SunGUIFillPath(const std::vector<glm::ivec2> &vertices) {
    // Copy the data (TODO: Generate Texture Coordinates)
    std::vector<glm::ivec2> data = vertices;

    // Generate the VBO and VAO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Write the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::ivec2) * data.size(), &data[0], GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, sizeof(glm::ivec2), (GLvoid *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
