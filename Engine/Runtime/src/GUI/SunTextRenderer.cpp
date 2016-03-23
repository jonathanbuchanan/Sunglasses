// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunTextRenderer.h"

void SunTextRenderer::init() {
    shader = SunShader("../../Engine/Shaders/Old/Text.vert", "../../Engine/Shaders/Old/Text.frag");
    projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

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
    // 0: Could not init FreeType
    // 1: Could not load font
    // 2: Could not load glyph
	SunLogger *logger = (SunLogger *)getService("logger");
    logger->log("Attempting to load " + _file + " as " + _name + ".");
    try {
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
            throw 0;

        FT_Face face;
        if (FT_New_Face(ft, _file.c_str(), 0, &face))
            throw 1;

        FT_Set_Pixel_Sizes(face, 0, 48);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        SunFont font;
        font.name = _name;

        for (GLubyte c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                throw 2;
                continue;
            }

            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            SunCharacter character = {texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), static_cast<GLuint> (face->glyph->advance.x)};
            font.characters.insert(std::pair<GLchar, SunCharacter>(c, character));
        }

        fonts.insert(std::pair<std::string, SunFont>(_name, font));

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        logger->logSuccess("Loaded " + _file + " as " + _name + ".");
    } catch (int e) {
        switch (e) {
            case 0:
                logger->logError("Couldn't init FreeType Library.");
                break;
            case 1:
                logger->logError("Couldn't load font.");
                break;
            case 2:
                logger->logError("Couldn't load glyph.");
                break;
        }
        logger->logError("Couldn't Load " + _file + " as " + _name + ".");
    }
}

void SunTextRenderer::renderText(std::string text, std::string _fontName, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
    shader.use();
    glUniform3f(shader.getUniformLocation("textColor"), color.x, color.y, color.z);
    glUniformMatrix4fv(shader.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    SunFont font = fonts[_fontName];

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        SunCharacter ch = font.characters[*c];

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
