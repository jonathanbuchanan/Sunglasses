// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/TexturedQuad.h>

namespace sunglasses {

void TexturedQuad::init() {
    addAction("render", &TexturedQuad::render);

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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // Bind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Initialize and write the data for the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    // Initialize and set the vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, textureCoordinates));

    // Unbind the VBO and EBO
    glBindVertexArray(0);
}

void TexturedQuad::render(Action action) {
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

} // namespace
