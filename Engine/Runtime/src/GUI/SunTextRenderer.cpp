// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunTextRenderer.h"

#include "SunFontResource.h"
#include "../ResourceManagement/SunResourceService.h"

void SunTextRenderer::init() {
    shader = SunShader("../../Engine/Shaders/Old/Text.vert", "../../Engine/Shaders/Old/Text.frag");
    projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

    ((SunResourceService *)getService("resource_service"))->addResourceManager("fonts", new SunResourceManager());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof (GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SunTextRenderer::loadFont(std::string _file, std::string _name) {
    // Load the font
    SunResource *font = new SunFontResource("Resources/Graphics/Fonts/arial.ttf");
    ((SunResourceService *)getService("resource_service"))->getResourceManager("fonts")->addResource("Arial", font);
}

void SunTextRenderer::renderText(std::string text, std::string _fontName, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
    shader.use();
    glUniform3f(shader.getUniformLocation("textColor"), color.x, color.y, color.z);
    glUniformMatrix4fv(shader.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    SunFontResource *font = (SunFontResource *)((SunResourceService *)getService("resource_service"))->getResourceManager("fonts")->getResource("Arial");

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        SunFontCharacter ch = font->getCharacters()[*c];

        GLfloat xpos = x + ch.bearing.x * scale;
        GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;

        GLfloat vertices[6][4] = {
            {xpos, ypos + h, 0.0, 0.0},
            {xpos, ypos, 0.0, 1.0},
            {xpos + w, ypos, 1.0, 1.0},

            {xpos, ypos + h, 0.0, 0.0},
            {xpos + w, ypos, 1.0, 1.0},
            {xpos + w, ypos + h, 1.0, 0.0}
        };

        glBindTexture(GL_TEXTURE_2D, ch.texture);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof (vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
