// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunShader.h"

std::string getShaderCodeFromFile(std::string filepath) {
    std::ifstream file(filepath);
    std::stringstream sourceStream;
    sourceStream << file.rdbuf();
    file.close();
    std::string str = sourceStream.str();
    return str;
}

GLuint compileShaderFromString(std::string shaderString, GLint shaderType) {
    const GLchar *shaderCode = shaderString.c_str();
    GLuint shader;
    GLint success;
    GLchar infoLog[2048];
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 2048, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return shader;
}

SunShader::SunShader() {

}

SunShader::SunShader(std::vector<std::pair<std::string, SunShaderSourceType>> sources) {
    size_t components = sources.size();

    std::vector<std::string> code;
    for (size_t i = 0; i < components; ++i) {
        code.push_back(getShaderCodeFromFile(sources[i].first));
    }

    std::vector<GLuint> shaders;
    for (size_t i = 0; i < components; ++i) {
        SunShaderSourceType type = sources[i].second;
        shaders.push_back(compileShaderFromString(code[i], type));
    }

    GLint success;
    GLchar infoLog[512];
    program = glCreateProgram();
    for (size_t i = 0; i < components; i++)
        glAttachShader(this->program, shaders[i]);
    glLinkProgram(this->program);
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program, 2048, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    for (size_t i = 0; i < components; ++i)
        glDeleteShader(shaders[i]);
}

void SunShader::init() {

}

void SunShader::uniforms(SunNode *root) {
    SunAction uniform("uniform");
    uniform.addParameter("shader", this);
    uniform.setRecursive(true);
    sendAction(uniform, root);
}

void SunShader::use() {
    for (auto &iterator : arrays)
        iterator.second = 0;
    usedTextureUnits = 0;

    glUseProgram(this->program);
}

void SunShader::use(std::string tag, float delta, SunNode *root) {
    use();

    uniforms(root);

    SunAction render("render");
    render.addParameter("shader", this);
    if (tag.length() > 0)
        render.addParameter("tag", &tag);
    render.setRecursive(true);
    sendAction(render, root);
}

void SunShader::send(std::string tag, float delta, SunNode *root) {
    uniforms(root);

    SunAction render("render");
    render.addParameter("shader", this);
    if (tag.length() > 0)
        render.addParameter("tag", &tag);
    render.setRecursive(true);
    sendAction(render, root);
}

int SunShader::getNextArrayIndex(std::string array) {
    if (arrays.find(array) == arrays.end())
        arrays[array] = 0;
    arrays[array] += 1;
    return arrays[array] - 1;
}

int SunShader::getNextTextureUnit() {
    return usedTextureUnits++;
}

int SunShader::getArraySize(std::string array) {
    return arrays[array];
}
