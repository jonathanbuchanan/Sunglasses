// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunTexturedQuad.h"

void SunTexturedQuad::setUpGL() {
    // Generate the VAO
    glGenVertexArrays(1, &VAO);

    // Generate the VBO and EBO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Initialize and write the data for the VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (SunVertex), &vertices[0], GL_STATIC_DRAW);

    // Bind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Initialize and write the data for the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof (GLuint), &indices[0], GL_STATIC_DRAW);

    // Initialize and set the vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (SunVertex), (GLvoid *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof (SunVertex), (GLvoid *)offsetof(SunVertex, textureCoordinates));

    // Unbind the VBO and EBO
    glBindVertexArray(0);
}

void SunTexturedQuad::render(std::map<std::string, std::pair<GLuint, GLuint>> _textures, SunShader _shader) {
    _shader.use();

    int iteratorIndex = 0;
    for (SunTextureMapIterator iterator = _textures.begin(); iterator != _textures.end(); iterator++) {
        glActiveTexture(GL_TEXTURE0 + iteratorIndex);
        glBindTexture(iterator->second.second, iterator->second.first);
        glUniform1i(_shader.getUniformLocation(iterator->first), iteratorIndex);

        iteratorIndex++;
    }

    // Bind the VAO
    glBindVertexArray(VAO);

    // Draw the triangles
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // Unbind the VAO
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void SunTexturedQuad::renderWithUsedShader(std::map<std::string, std::pair<GLuint, GLuint>> _textures, SunShader _shader) {
    int iteratorIndex = 0;
    for (SunTextureMapIterator iterator = _textures.begin(); iterator != _textures.end(); iterator++) {
        glActiveTexture(GL_TEXTURE0 + iteratorIndex);
        glBindTexture(iterator->second.second, iterator->second.first);
        glUniform1i(_shader.getUniformLocation(iterator->first), iteratorIndex);

        iteratorIndex++;
    }
    glActiveTexture(GL_TEXTURE0);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Draw the triangles
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // Unbind the VAO
    glBindVertexArray(0);
}
