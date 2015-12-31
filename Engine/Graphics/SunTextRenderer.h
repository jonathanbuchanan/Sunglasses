// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef OpenGL_Test_3_SunTextRenderer_h
#define OpenGL_Test_3_SunTextRenderer_h

#include <map>
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ft2build.h"
#include FT_FREETYPE_H

#include "./Shaders/SunShader.h"

#include "../Libraries/glm/glm.hpp"
#include "../Libraries/glm/gtc/matrix_transform.hpp"
#include "../Libraries/glm/gtc/type_ptr.hpp"
#include "../Libraries/glm/gtc/quaternion.hpp"
#include "../Libraries/glm/gtx/quaternion.hpp"
#include "../Libraries/glm/gtx/string_cast.hpp"

using namespace std;

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
    SunTextRenderer() { }
    
    void initialize();
    void loadFont(string _file, string _name);
    void renderText(string text, string _fontName, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    
    inline map<string, SunFont> & getFonts() { return fonts; }
    inline SunFont & getFontForString(string s) { return fonts[s]; }
    inline void addFontForString(string s, SunFont font) { fonts[s] = font; }
    
    inline glm::mat4 & getProjectionMatrix() { return projection; }
    
    inline SunShader & getShader() { return shader; }
    inline void setShader(SunShader _shader) { shader = _shader; }
    
    inline GLuint getVAO() { return VAO; }
    inline GLuint getVBO() { return VBO; }
private:
    map<string, SunFont> fonts;

    glm::mat4 projection;

    SunShader shader;

    GLuint VAO;
    GLuint VBO;
};

#endif
