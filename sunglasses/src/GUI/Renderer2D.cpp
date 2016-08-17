// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/Renderer2D.h>

#include <sunglasses/GUI/Window.h>

#include <string>

#include <glm/gtc/matrix_transform.hpp>

namespace sunglasses {
namespace GUI {

const std::string fill_vertex = R"(
#version 330 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 texCoords;

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

const std::string texture_vertex = R"(
#version 330 core

layout (location = 0) in vec2 vertex;
layout (loaction = 1) in vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;

out VertexOut {
    vec2 texCoords;
} vertexOut;

void main() {
    gl_position = projection * model * vec4(vertex, 0.0f, 1.0f);
    vertexOut.texCoords = texCoords;
}
)";

const std::string texture_fragment = R"(
#version 330 core

out vec4 color;

in VertexOut {
    vec2 texCoords;
} fragmentIn;

uniform sampler2D sampler;

void main() {
    color = texture(sampler, fragmentIn.texCoords);
}
)";

Renderer2D::Renderer2D(Window &_window) :
    window(_window), fillShader(fill_vertex, fill_fragment) {

}

void Renderer2D::draw(glm::ivec2 origin, glm::ivec2 size, glm::vec4 color) {
    fillShader.use();

    // Pass the projection matrix
    fillShader["projection"] = window.projection();

    // Generate a model matrix
    glm::mat4 model;

    model = glm::translate(model, glm::vec3(origin, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    fillShader["model"] = model;

    // Pass the uniforms of the drawable
    fillShader["fillColor"] = color;

    glBindVertexArray(rectangle.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer2D::draw(glm::ivec2 origin, glm::ivec2 size, Texture &texture) {
    
}

Renderer2D::Rectangle::Rectangle() {
    // Generate the VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate the VBO and EBO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Load the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Load the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Unbind all buffers
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace
} // namespace
