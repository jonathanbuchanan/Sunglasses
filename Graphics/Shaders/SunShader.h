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

#include <GL/glew.h>

typedef void * SunShaderUniformValuePointer;

// SunShaderUniform Declaration
struct SunShaderUniform {
    // Name, type, and value pointer;
    string name;
    string type;
    SunShaderUniformValuePointer value;
    
    SunShaderUniform() {
        
    }
    
    SunShaderUniform(string _name, string _type, SunShaderUniformValuePointer _value) {
        name = _name;
        type = _type;
        value = _value;
    }
};

typedef map<string, SunShaderUniform>::iterator SunShaderUniformMapIterator;

class SunShader {
public:
    GLuint program;
    map<string, SunShaderUniform> uniforms;
    
    SunShader() {
        
    }
    
    SunShader(const GLchar *vertexPath, const GLchar *fragmentPath) {
        std::string vertexCode;
        std::string fragmentCode;
        try {
            std::ifstream vShaderFile(vertexPath);
            std::ifstream fShaderFile(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::exception e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar *vShaderCode = vertexCode.c_str();
        const GLchar *fShaderCode = fragmentCode.c_str();
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
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
    
    SunShader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *_preprocessor, string _type) {
        std::string vertexCode;
        std::string fragmentCode;
        try {
            std::ifstream vShaderFile(vertexPath);
            std::ifstream fShaderFile(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::exception e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar *vShaderCode = vertexCode.c_str();
        const GLchar *fShaderCode = fragmentCode.c_str();
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];
        vertex = glCreateShader(GL_VERTEX_SHADER);
        const GLchar *vertexSources[2] = {vShaderCode, _preprocessor};
        glShaderSource(vertex, 1, vertexSources, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar *fragmentSources[2] = {fShaderCode, _preprocessor};
        glShaderSource(fragment, 1, fragmentSources, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
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
    
    SunShader(const GLchar *vertexPath, const GLchar *geometryPath, const GLchar *fragmentPath) {
        std::string vertexCode;
        std::string geometryCode;
        std::string fragmentCode;
        try {
            std::ifstream vShaderFile(vertexPath);
            std::ifstream gShaderFile(geometryPath);
            std::ifstream fShaderFile(fragmentPath);
            std::stringstream vShaderStream, gShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            gShaderStream << gShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            gShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            geometryCode = gShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::exception e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar *vShaderCode = vertexCode.c_str();
        const GLchar *gShaderCode = geometryCode.c_str();
        const GLchar *fShaderCode = fragmentCode.c_str();
        GLuint vertex, geometry, fragment;
        GLint success;
        GLchar infoLog[512];
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(geometry, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
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
    
    void use() {
        glUseProgram(this->program);
        passPerShaderUniforms(this->program);
    }
    
    void passPerShaderUniforms(GLuint _program) {
        for (SunShaderUniformMapIterator iterator = uniforms.begin(); iterator != uniforms.end(); iterator++) {
            if (iterator->second.type == "float")
                glUniform1f(glGetUniformLocation(_program, iterator->second.name.c_str()), *(GLfloat *)iterator->second.value);
            else if (iterator->second.type == "boolean")
                glUniform1i(glGetUniformLocation(_program, iterator->second.name.c_str()), *(GLboolean *)iterator->second.value);
        }
    }
};

#endif
