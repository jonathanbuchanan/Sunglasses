// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/SunShader.h>

#include <glm/gtc/type_ptr.hpp>

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

SunShader::SunShader(const std::string &vertex, const std::string &fragment) {
    GLuint vertexShader = compileShaderFromString(vertex, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShaderFromString(fragment, GL_FRAGMENT_SHADER);

    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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

SunShader::SunShaderUniform SunShader::operator[](std::string uniform) {
    return SunShaderUniform(program, glGetUniformLocation(program, uniform.c_str()));
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

SunShader::SunShaderUniform::SunShaderUniform(
    GLuint _program, GLuint _index) :
    program(_program), index(_index) {

}

void SunShader::SunShaderUniform::operator=(GLfloat value) {
    glUniform1f(index, value);
}

void SunShader::SunShaderUniform::operator=(glm::vec2 value) {
    glUniform2f(index, value.x, value.y);
}

void SunShader::SunShaderUniform::operator=(glm::vec3 value) {
    glUniform3f(index, value.x, value.y, value.z);
}

void SunShader::SunShaderUniform::operator=(glm::vec4 value) {
    glUniform4f(index, value.x, value.y, value.z, value.w);
}


void SunShader::SunShaderUniform::operator=(GLint value) {
    glUniform1i(index, value);
}

void SunShader::SunShaderUniform::operator=(glm::ivec2 value) {
    glUniform2i(index, value.x, value.y);
}

void SunShader::SunShaderUniform::operator=(glm::ivec3 value) {
    glUniform3i(index, value.x, value.y, value.z);
}

void SunShader::SunShaderUniform::operator=(glm::ivec4 value) {
    glUniform4i(index, value.x, value.y, value.z, value.w);
}


void SunShader::SunShaderUniform::operator=(GLuint value) {
    glUniform1ui(index, value);
}

void SunShader::SunShaderUniform::operator=(glm::uvec2 value) {
    glUniform2ui(index, value.x, value.y);
}

void SunShader::SunShaderUniform::operator=(glm::uvec3 value) {
    glUniform3ui(index, value.x, value.y, value.z);
}

void SunShader::SunShaderUniform::operator=(glm::uvec4 value) {
    glUniform4ui(index, value.x, value.y, value.z, value.w);
}


void SunShader::SunShaderUniform::operator=(glm::mat2 value) {
    glUniformMatrix2fv(index, 1, GL_FALSE, glm::value_ptr(value));
}

void SunShader::SunShaderUniform::operator=(glm::mat3 value) {
    glUniformMatrix3fv(index, 1, GL_FALSE, glm::value_ptr(value));
}

void SunShader::SunShaderUniform::operator=(glm::mat4 value) {
    glUniformMatrix4fv(index, 1, GL_FALSE, glm::value_ptr(value));
}


void SunShader::SunShaderUniform::operator=(glm::mat2x3 value) {
    glUniformMatrix2x3fv(index, 1, GL_FALSE, glm::value_ptr(value));
}

void SunShader::SunShaderUniform::operator=(glm::mat3x2 value) {
    glUniformMatrix3x2fv(index, 1, GL_FALSE, glm::value_ptr(value));
}

void SunShader::SunShaderUniform::operator=(glm::mat2x4 value) {
    glUniformMatrix2x4fv(index, 1, GL_FALSE, glm::value_ptr(value));
}

void SunShader::SunShaderUniform::operator=(glm::mat4x2 value) {
    glUniformMatrix4x2fv(index, 1, GL_FALSE, glm::value_ptr(value));
}

void SunShader::SunShaderUniform::operator=(glm::mat3x4 value) {
    glUniformMatrix3x4fv(index, 1, GL_FALSE, glm::value_ptr(value));
}

void SunShader::SunShaderUniform::operator=(glm::mat4x3 value) {
    glUniformMatrix4x3fv(index, 1, GL_FALSE, glm::value_ptr(value));
}
