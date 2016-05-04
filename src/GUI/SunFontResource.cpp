// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunFontResource.h"

#include <ft2build.h>
#include FT_FREETYPE_H

SunFontResource::SunFontResource(std::string _path) : path(_path) {

}

void SunFontResource::init() {
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        throw 0;

    FT_Face face;
    if (FT_New_Face(ft, path.c_str(), 0, &face))
        throw 1;

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
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

        SunFontCharacter character;
        character.texture = texture;
        character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
        character.advance = (GLuint)face->glyph->advance.x;
        characters[c] = character;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}
