// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNSHADER_H
#define SUNSHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>

#include "../Core/SunNode.h"
#include "../Output/SunLogger.h"

enum SunShaderSourceType {
    SunShaderSourceTypeVertex = GL_VERTEX_SHADER,
    SunShaderSourceTypeFragment = GL_FRAGMENT_SHADER,
    SunShaderSourceTypeGeometry = GL_GEOMETRY_SHADER
};

extern std::string getShaderCodeFromFile(std::string filepath);
extern GLuint compileShaderFromString(std::string shaderString, GLint shaderType);
extern GLuint compileShaderFromStrings(std::vector<std::string> shaderStrings, GLint shaderType);

class SunShader : public SunBase {
public:
    SunShader() { }

    SunShader(std::string vertexPath, std::string fragmentPath);
    SunShader(std::string vertexPath, std::string fragmentPath, std::string preprocessorPath);
    SunShader(std::string vertexPath, std::string geometryPath, std::string fragmentPath, std::string preprocessorPath);
    SunShader(std::vector<std::string> sources, std::vector<SunShaderSourceType> sourceTypes, std::string preprocessorPath);
    SunShader(std::string vertexPath, std::string geometryPath, std::string fragmentPath, int a);

    void init();

	void uniforms(SunNode *root);

    void use();
	void use(std::string tag, float delta, SunNode *root);
	void send(std::string tag, float delta, SunNode *root);

    inline GLuint getProgram() { return program; }
    inline void setProgram(GLuint _program) { program = _program; }
    inline GLuint getUniformLocation(std::string uniform) { return glGetUniformLocation(program, uniform.c_str()); }
private:
    GLuint program;
};

#endif
