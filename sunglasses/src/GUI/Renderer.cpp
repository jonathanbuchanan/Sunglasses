// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/Renderer.h>

#include <sunglasses/GUI/Window.h>

#include <string>

#include <glm/gtc/matrix_transform.hpp>

namespace sunglasses {

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

Renderer::Renderer(Window &_window) :
    window(_window), fillShader(fill_vertex, fill_fragment) {

}

void Renderer::drawRect(glm::ivec2 origin, glm::ivec2 size, Drawable *drawable) {
    fillShader.use();

    // Pass the projection matrix
    fillShader["projection"] = window.projection();

    // Generate a model matrix
    glm::mat4 model;

    model = glm::translate(model, glm::vec3(origin, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    fillShader["model"] = model;

    // Pass the uniforms of the drawable
    drawable->uniforms(fillShader);

    glBindVertexArray(rectangle.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Renderer::Rectangle::Rectangle() {
    // Generate the VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate the VBO and EBO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Load the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribIPointer(0, 2, GL_INT, 2 * sizeof(GLint), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    // Load the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Unbind all buffers
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace
