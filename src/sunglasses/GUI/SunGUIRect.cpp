// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGUIRect.h"

#include <sunglasses/Graphics/SunShader.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLuint SunGUIRect::VBO, SunGUIRect::EBO, SunGUIRect::VAO = 0;

bool SunGUIRect::GLinitialized = false;

const GLint SunGUIRect::vertices[] = {
    0, 0,
    0, 1,
    1, 0,
    1, 1
};

const GLuint SunGUIRect::indices[] = {
    0, 1, 2,
    1, 2, 3
};

SunGUIRect::SunGUIRect(glm::ivec2 _origin, glm::ivec2 _size) :
    origin(_origin), size(_size) {
    createBuffers();
}

void SunGUIRect::draw(SunShader &shader, glm::mat4 projectionMatrix, glm::vec4 color) const {
    // Pass the projection matrix
    shader["projection"] = projectionMatrix;

    // Generate a model matrix
    glm::mat4 model;

    model = glm::translate(model, glm::vec3(origin, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    shader["model"] = model;

    // Pass the color
    shader["fillColor"] = color;

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void SunGUIRect::createBuffers() {
    // Stop if this is already done
    if (GLinitialized)
        return;

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

    GLinitialized = true;
}
