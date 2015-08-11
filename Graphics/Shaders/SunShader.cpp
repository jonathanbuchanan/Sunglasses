#include "SunShader.h"

string getShaderCodeFromFile(string filepath) {
    ifstream file = ifstream(filepath);
    stringstream sourceStream;
    sourceStream << file.rdbuf();
    file.close();
    string str = sourceStream.str();
    return str;
}

GLuint compileShaderFromString(string shaderString, GLint shaderType) {
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

GLuint compileShaderFromStrings(vector<string> shaderStrings, GLint shaderType) {
    const GLchar *sources[shaderStrings.size()];
    for (int i = 0; i < shaderStrings.size(); i++) {
        sources[i] = shaderStrings[i].c_str();
    }
    GLuint shader;
    GLint success;
    GLchar infoLog[512];
    shader = glCreateShader(shaderType);
    glShaderSource(shader, shaderStrings.size(), sources, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return shader;

}

SunShader::SunShader(string vertexPath, string fragmentPath) {
    string vertexCode = getShaderCodeFromFile(vertexPath);
    string fragmentCode = getShaderCodeFromFile(fragmentPath);

    GLuint vertex = compileShaderFromString(vertexCode, GL_VERTEX_SHADER);
    GLuint fragment = compileShaderFromString(fragmentCode, GL_FRAGMENT_SHADER);

    GLint success;
    GLchar infoLog[512];
    this->program = glCreateProgram();
    glAttachShader(this->program, vertex);
    glAttachShader(this->program, fragment);
    glLinkProgram(this->program);
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

SunShader::SunShader(string vertexPath, string fragmentPath, string preprocessorPath, string version) {
    string vertexCode = getShaderCodeFromFile(vertexPath);
    string fragmentCode = getShaderCodeFromFile(fragmentPath);
    string preprocessorCode = getShaderCodeFromFile(preprocessorPath);
    string _version = "#version 330 core\n";

    vector<string> vertexStrings = {_version, preprocessorCode, vertexCode};
    vector<string> fragmentStrings = {_version, preprocessorCode, fragmentCode};

    GLuint vertex = compileShaderFromStrings(vertexStrings, GL_VERTEX_SHADER);
    GLuint fragment = compileShaderFromStrings(fragmentStrings, GL_FRAGMENT_SHADER);

    GLint success;
    GLchar infoLog[512];
    this->program = glCreateProgram();
    glAttachShader(this->program, vertex);
    glAttachShader(this->program, fragment);
    glLinkProgram(this->program);
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program, 2048, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

SunShader::SunShader(string vertexPath, string geometryPath, string fragmentPath) {
    string vertexCode = getShaderCodeFromFile(vertexPath);
    string geometryCode = getShaderCodeFromFile(geometryPath);
    string fragmentCode = getShaderCodeFromFile(fragmentPath);
    
    GLuint vertex = compileShaderFromString(vertexCode, SunShaderSourceTypeVertex);
    GLuint geometry = compileShaderFromString(geometryCode, SunShaderSourceTypeGeometry);
    GLuint fragment = compileShaderFromString(fragmentCode, SunShaderSourceTypeFragment);
    
    GLint success;
    GLchar infoLog[512];
    this->program = glCreateProgram();
    glAttachShader(this->program, vertex);
    glAttachShader(this->program, geometry);
    glAttachShader(this->program, fragment);
    glLinkProgram(this->program);
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(geometry);
    glDeleteShader(fragment);
}

void SunShader::use() {
    glUseProgram(this->program);
}