//
//  SunShader.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/17/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_SunShader_h
#define OpenGL_Test_3_SunShader_h

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

#include <GL/glew.h>

enum SunShaderSourceType {
    SunShaderSourceTypeVertex = GL_VERTEX_SHADER,
    SunShaderSourceTypeFragment = GL_FRAGMENT_SHADER,
    SunShaderSourceTypeGeometry = GL_GEOMETRY_SHADER
};

extern string getShaderCodeFromFile(string filepath);
extern GLuint compileShaderFromString(string shaderString, GLint shaderType);
extern GLuint compileShaderFromStrings(vector<string> shaderStrings, GLint shaderType);

class SunShader {
public:
    SunShader() { }
    
    SunShader(string vertexPath, string fragmentPath);
    SunShader(string vertexPath, string fragmentPath, string preprocessorPath, string version);
    SunShader(string vertexPath, string geometryPath, string fragmentPath);
    
    void use();
    
    inline GLuint getProgram() { return program; }
    inline void setProgram(GLuint _program) { program = _program; }
    inline GLuint getUniformLocation(string uniform) { return glGetUniformLocation(program, uniform.c_str()); }
private:
    GLuint program;
};

#endif
