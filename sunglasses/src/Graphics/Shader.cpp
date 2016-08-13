// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/Shader.h>

#include <glm/gtc/type_ptr.hpp>

#include <sunglasses/Graphics/Texture.h>

namespace sunglasses {

Shader::TextureUnit::TextureUnit(GLuint _unit) : unit(_unit) {

}

void Shader::TextureUnit::operator=(Texture &texture) {
    // Activate this texture unit
    glActiveTexture(GL_TEXTURE0 + unit);

    // Bind the texture
    //glBindTexture(GL_TEXTURE_2D, texture.texture);

    // Assign the uniform
    glUniform1i(0, unit);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

Shader::TextureMapper::TextureMapper(std::initializer_list<std::string> textureList) {
    // Iterate through the list, make a new texture unit for each entry
    GLuint unit = 0;
    for (auto &string : textureList) {
        textureUnits.emplace(string, unit);
        ++unit;
    }
}

Shader::TextureUnit Shader::TextureMapper::operator[](std::string textureName) {

}

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

Shader::Shader(const std::string &vertex, const std::string &fragment,
        std::initializer_list<std::string> _textures) : textures(_textures) {
    GLuint vertexShader = compileShaderFromString(vertex, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShaderFromString(fragment, GL_FRAGMENT_SHADER);

    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::Shader(std::vector<std::pair<std::string, ShaderSourceType>> sources,
        std::initializer_list<std::string> _textures) : textures(_textures) {
    size_t components = sources.size();

    std::vector<std::string> code;
    for (size_t i = 0; i < components; ++i) {
        code.push_back(getShaderCodeFromFile(sources[i].first));
    }

    std::vector<GLuint> shaders;
    for (size_t i = 0; i < components; ++i) {
        ShaderSourceType type = sources[i].second;
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

Shader::~Shader() {
    glDeleteProgram(program);

    std::cout << "~Shader()" << std::endl;
}

Shader::ShaderUniform Shader::operator[](std::string uniform) {
    return ShaderUniform(program, glGetUniformLocation(program, uniform.c_str()));
}

void Shader::init() {

}

void Shader::uniforms(Node *root) {
    Action uniform("uniform");
    uniform.addParameter("shader", this);
    uniform.setRecursive(true);
    sendAction(uniform, root);
}

void Shader::use() {
    for (auto &iterator : arrays)
        iterator.second = 0;
    usedTextureUnits = 0;

    glUseProgram(this->program);
}

void Shader::use(std::string tag, float delta, Node *root) {
    use();

    uniforms(root);

    Action render("render");
    render.addParameter("shader", this);
    if (tag.length() > 0)
        render.addParameter("tag", &tag);
    render.setRecursive(true);
    sendAction(render, root);
}

void Shader::send(std::string tag, float delta, Node *root) {
    uniforms(root);

    Action render("render");
    render.addParameter("shader", this);
    if (tag.length() > 0)
        render.addParameter("tag", &tag);
    render.setRecursive(true);
    sendAction(render, root);
}

int Shader::getNextArrayIndex(std::string array) {
    if (arrays.find(array) == arrays.end())
        arrays[array] = 0;
    arrays[array] += 1;
    return arrays[array] - 1;
}

int Shader::getNextTextureUnit() {
    return usedTextureUnits++;
}

int Shader::getArraySize(std::string array) {
    return arrays[array];
}

Shader::ShaderUniform::ShaderUniform(
    GLuint _program, GLuint _index) :
    program(_program), index(_index) {

}

void Shader::ShaderUniform::operator=(GLfloat value) {
    glUniform1f(index, value);
}

void Shader::ShaderUniform::operator=(GLdouble value) {
    glUniform1f(index, (GLfloat)value);
}

void Shader::ShaderUniform::operator=(glm::vec2 value) {
    glUniform2f(index, value.x, value.y);
}

void Shader::ShaderUniform::operator=(glm::vec3 value) {
    glUniform3f(index, value.x, value.y, value.z);
}

void Shader::ShaderUniform::operator=(glm::vec4 value) {
    glUniform4f(index, value.x, value.y, value.z, value.w);
}


void Shader::ShaderUniform::operator=(GLint value) {
    glUniform1i(index, value);
}

void Shader::ShaderUniform::operator=(GLboolean value) {
    glUniform1i(index, (GLint)value);
}

void Shader::ShaderUniform::operator=(glm::ivec2 value) {
    glUniform2i(index, value.x, value.y);
}

void Shader::ShaderUniform::operator=(glm::ivec3 value) {
    glUniform3i(index, value.x, value.y, value.z);
}

void Shader::ShaderUniform::operator=(glm::ivec4 value) {
    glUniform4i(index, value.x, value.y, value.z, value.w);
}


void Shader::ShaderUniform::operator=(GLuint value) {
    glUniform1ui(index, value);
}

void Shader::ShaderUniform::operator=(glm::uvec2 value) {
    glUniform2ui(index, value.x, value.y);
}

void Shader::ShaderUniform::operator=(glm::uvec3 value) {
    glUniform3ui(index, value.x, value.y, value.z);
}

void Shader::ShaderUniform::operator=(glm::uvec4 value) {
    glUniform4ui(index, value.x, value.y, value.z, value.w);
}


void Shader::ShaderUniform::operator=(glm::mat2 value) {
    glUniformMatrix2fv(index, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::ShaderUniform::operator=(glm::mat3 value) {
    glUniformMatrix3fv(index, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::ShaderUniform::operator=(glm::mat4 value) {
    glUniformMatrix4fv(index, 1, GL_FALSE, glm::value_ptr(value));
}


void Shader::ShaderUniform::operator=(glm::mat2x3 value) {
    glUniformMatrix2x3fv(index, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::ShaderUniform::operator=(glm::mat3x2 value) {
    glUniformMatrix3x2fv(index, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::ShaderUniform::operator=(glm::mat2x4 value) {
    glUniformMatrix2x4fv(index, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::ShaderUniform::operator=(glm::mat4x2 value) {
    glUniformMatrix4x2fv(index, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::ShaderUniform::operator=(glm::mat3x4 value) {
    glUniformMatrix3x4fv(index, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::ShaderUniform::operator=(glm::mat4x3 value) {
    glUniformMatrix4x3fv(index, 1, GL_FALSE, glm::value_ptr(value));
}





} // namespace
