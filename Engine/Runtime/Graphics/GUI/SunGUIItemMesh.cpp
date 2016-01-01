// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGUIItemMesh.h"

void SunGUIItemMesh::setUpGL() {
    glGenVertexArrays(1, &VAO);

    // Generate the VBO and EBO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Initialize and write the data for the VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (SunBasicVertex), &vertices[0], GL_STATIC_DRAW);

    // Bind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Initialize and write the data for the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof (GLuint), &indices[0], GL_STATIC_DRAW);

    // Initialize and set the vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof (SunBasicVertex), (GLvoid *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof (SunBasicVertex), (GLvoid *) offsetof(SunBasicVertex, textureCoordinates));

    // Unbind the VBO and EBO
    glBindVertexArray(0);
}

void SunGUIItemMesh::loadTexture(string texturePath) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width, height;
    unsigned char *image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    SOIL_free_image_data(image);

    texture = textureID;
}

void SunGUIItemMesh::render(glm::vec2 _position, glm::vec2 _size, glm::vec3 _color, GLboolean _textured, glm::vec3 _highlightColor, GLboolean _highlighted, string _text, string _font, SunTextRenderer* _renderer) {
    // Use the Shader
    shader.use();

    glm::mat4 model;
    model = glm::translate(model, glm::vec3(_position, 0.0f));
    model = glm::scale(model, glm::vec3(_size, 1.0f));

    glUniformMatrix4fv(shader.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform3f(shader.getUniformLocation("_color"), _color.r, _color.g, _color.b);
    glUniform1i(shader.getUniformLocation("_textured"), _textured);
    glUniform3f(shader.getUniformLocation("_highlightColor"), _highlightColor.r, _highlightColor.g, _highlightColor.b);
    glUniform1i(shader.getUniformLocation("_highlighted"), _highlighted);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(shader.getUniformLocation("_texture"), 0);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Draw the triangles
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // Unbind the VAO
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);

    // Render the text
    if (_renderer != NULL)
        _renderer->renderText(_text, _font, (_position.x + 1) * 400, (_position.y + 1) * 300, 1, glm::vec3(0.0, 0.0, 0.0));
}