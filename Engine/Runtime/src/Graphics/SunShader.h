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
#include <map>

using namespace std;

#include <GL/glew.h>

#include "../Core/SunNode.h"
#include "../Output/SunLogger.h"

enum SunShaderSourceType {
    SunShaderSourceTypeVertex = GL_VERTEX_SHADER,
    SunShaderSourceTypeFragment = GL_FRAGMENT_SHADER,
    SunShaderSourceTypeGeometry = GL_GEOMETRY_SHADER
};

extern string getShaderCodeFromFile(string filepath);
extern GLuint compileShaderFromString(string shaderString, GLint shaderType);
extern GLuint compileShaderFromStrings(vector<string> shaderStrings, GLint shaderType);

class SunShader : public SunBase {
public:
    SunShader() { }

    SunShader(string vertexPath, string fragmentPath);
    SunShader(string vertexPath, string fragmentPath, string preprocessorPath);
    SunShader(string vertexPath, string geometryPath, string fragmentPath, string preprocessorPath);
    SunShader(vector<string> sources, vector<SunShaderSourceType> sourceTypes, string preprocessorPath);
    SunShader(string vertexPath, string geometryPath, string fragmentPath, int a);

    void init();

	void uniforms(SunNode *root);

    void use();
	void use(std::string tag, float delta, SunNode *root);
	void send(std::string tag, float delta, SunNode *root);

    /// Returns the next index of an array in the shader.
    /**
     * This function is useful when populating an array in the shader. The object
     * maintains a map of array names and sizes. This method returns the next index
     * for the array. If the array is not in the map already, it adds the array
     * to the map ands sets its value to 0. Every array is cleared during the use()
     * method.
     * @param array The name of the array
     */
    int getNextArrayIndex(std::string array);

    /// Returns the size of an array in the shader.
    /**
     * This method is useful when populating an array in the shader.
     * @see getNextArrayIndex()
     * @param array The name of the array
     */
    int getArraySize(std::string array);

    GLuint getProgram() { return program; }
    GLuint getUniformLocation(string uniform) { return glGetUniformLocation(program, uniform.c_str()); }
private:
    std::map<std::string, int> arrays;

    GLuint program;
};

#endif
