//
//  SunTextRenderer.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/25/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_SunTextRenderer_h
#define OpenGL_Test_3_SunTextRenderer_h

using namespace std;

#include <map>
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ft2build.h"
#include FT_FREETYPE_H

#include "SunShader.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtc/quaternion.hpp"
#include "../glm/gtx/quaternion.hpp"
#include "../glm/gtx/string_cast.hpp"

struct SunCharacter {
    GLuint texture;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint advance;
};

struct SunFont {
    string name;
    std::map <GLchar, SunCharacter> characters;
};

class SunTextRenderer {
public:
    std::map<string, SunFont> fonts;
    
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    
    SunShader shader;
    
    GLuint VAO;
    GLuint VBO;
    
    void initialize() {
        shader = SunShader("Graphics/Shaders/TextVertex.vert", "Graphics/Shaders/TextFragment.frag");
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    void loadFont(string _file, string _name) {
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        
        FT_Face face;
        if (FT_New_Face(ft, _file.c_str(), 0, &face))
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        
        FT_Set_Pixel_Sizes(face, 0, 48);
        
        if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
        SunFont font;
        font.name = _name;
        
        for (GLubyte c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
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
            
            SunCharacter character = {texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), static_cast<GLuint>(face->glyph->advance.x)};
            font.characters.insert(std::pair<GLchar, SunCharacter>(c, character));
        }
        
        fonts.insert(std::pair<string, SunFont>(_name, font));
        
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }
    
    void renderText(string text, string _fontName, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
        shader.use();
        glUniform3f(glGetUniformLocation(shader.program, "textColor"), color.x, color.y, color.z);
        glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
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
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            glDrawArrays(GL_TRIANGLES, 0, 6);
            
            x += (ch.advance >> 6) * scale;
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
private:
    
};

#endif
