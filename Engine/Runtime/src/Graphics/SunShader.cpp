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

GLuint compileShaderFromStrings(std::vector<std::string> shaderStrings, GLint shaderType) {
    const GLchar *sources[shaderStrings.size()];
    for (size_t i = 0; i < shaderStrings.size(); i++) {
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
    }
    return shader;

}

SunShader::SunShader(std::string vertexPath, std::string fragmentPath) {
	((SunLogger *)getService("logger"))->log("Attempting to load shader from " + vertexPath + " and " + fragmentPath);
    std::string vertexCode = getShaderCodeFromFile(vertexPath);
    std::string fragmentCode = getShaderCodeFromFile(fragmentPath);

	GLchar infoLog[512];

	try {
		GLuint vertex = compileShaderFromString(vertexCode, GL_VERTEX_SHADER);
	    GLuint fragment = compileShaderFromString(fragmentCode, GL_FRAGMENT_SHADER);

	    GLint success;
		this->program = glCreateProgram();
	    glAttachShader(this->program, vertex);
		glAttachShader(this->program, fragment);
		glLinkProgram(this->program);
		glGetProgramiv(this->program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->program, 512, NULL, infoLog);
			throw 0;
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	} catch (int e) {
		switch (e) {
			case 0:
				((SunLogger *)getService("logger"))->logError("Shader Linking Failed\n" + std::string(infoLog));
				break;
		}
		return;
	}
	((SunLogger *)getService("logger"))->logSuccess("Linked Shader");
}

SunShader::SunShader(std::string vertexPath, std::string fragmentPath, std::string preprocessorPath) {
	((SunLogger *)getService("logger"))->log("Attempting to load shader from " + vertexPath + ", " + fragmentPath + ", and " + preprocessorPath);
    std::string vertexCode = getShaderCodeFromFile(vertexPath);
    std::string fragmentCode = getShaderCodeFromFile(fragmentPath);
    std::string preprocessorCode = getShaderCodeFromFile(preprocessorPath);
    std::string _version = "#version 330 core\n";

    std::vector<std::string> vertexStrings = {_version, preprocessorCode, vertexCode};
    std::vector<std::string> fragmentStrings = {_version, preprocessorCode, fragmentCode};

    GLuint vertex = compileShaderFromStrings(vertexStrings, GL_VERTEX_SHADER);
    GLuint fragment = compileShaderFromStrings(fragmentStrings, GL_FRAGMENT_SHADER);

    GLint success;
    GLchar infoLog[512];
	try {
		this->program = glCreateProgram();
		glAttachShader(this->program, vertex);
		glAttachShader(this->program, fragment);
		glLinkProgram(this->program);
		glGetProgramiv(this->program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->program, 2048, NULL, infoLog);
			throw 0;
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	} catch (int e) {
		switch (e) {
			case 0:
				((SunLogger *)getService("logger"))->logError("Shader Linking Failed\n" + std::string(infoLog));
				break;
		}
		return;
	}
	((SunLogger *)getService("logger"))->logSuccess("Linked Shader");
}

SunShader::SunShader(std::string vertexPath, std::string geometryPath, std::string fragmentPath, std::string preprocessorPath) {
	((SunLogger *)getService("logger"))->log("Attempting to load shader from " + vertexPath + ", " + geometryPath + ", " + fragmentPath + ", and " + preprocessorPath);
    std::string vertexCode = getShaderCodeFromFile(vertexPath);
    std::string geometryCode = getShaderCodeFromFile(geometryPath);
    std::string fragmentCode = getShaderCodeFromFile(fragmentPath);
    std::string preprocessorCode = getShaderCodeFromFile(preprocessorPath);
    std::string _version = "#version 330 core\n";

    std::vector<std::string> vertexStrings = {_version, preprocessorCode, vertexCode};
    std::vector<std::string> geometryStrings = {_version, preprocessorCode, geometryCode};
    std::vector<std::string> fragmentStrings = {_version, preprocessorCode, fragmentCode};

    GLuint vertex = compileShaderFromStrings(vertexStrings, GL_VERTEX_SHADER);
    GLuint geometry = compileShaderFromStrings(geometryStrings, GL_GEOMETRY_SHADER);
    GLuint fragment = compileShaderFromStrings(fragmentStrings, GL_FRAGMENT_SHADER);

    GLint success;
    GLchar infoLog[512];
	try {
		this->program = glCreateProgram();
		glAttachShader(this->program, vertex);
		glAttachShader(this->program, geometry);
		glAttachShader(this->program, fragment);
		glLinkProgram(this->program);
		glGetProgramiv(this->program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->program, 2048, NULL, infoLog);
			throw 0;
		}
		glDeleteShader(vertex);
		glDeleteShader(geometry);
		glDeleteShader(fragment);
	} catch (int e) {
		switch (e) {
			case 0:
				((SunLogger *)getService("logger"))->logError("Shader Linking Failed\n" + std::string(infoLog));
				break;
		}
		return;
	}
	((SunLogger *)getService("logger"))->logSuccess("Linked Shader");
}

SunShader::SunShader(std::vector<std::string> sources, std::vector<SunShaderSourceType> sourceTypes, std::string preprocessorPath) {
    int components = sources.size();

    std::string _version = "#version 330 core\n";
    std::string preprocessorCode = getShaderCodeFromFile(preprocessorPath);
    std::vector<std::string> code;
    for (int i = 0; i < components; i++)
        code.push_back(getShaderCodeFromFile(sources[i]));

    std::vector<std::vector<std::string>> strings;
    for (int i = 0; i < components; i++) {
        strings.push_back({_version, preprocessorCode, code[i]});
    }

    std::vector<GLuint> shaders;
    for (int i = 0; i < components; i++)
        shaders.push_back(compileShaderFromStrings(strings[i], sourceTypes[i]));

    GLint success;
    GLchar infoLog[512];
    this->program = glCreateProgram();
    for (int i = 0; i < components; i++)
        glAttachShader(this->program, shaders[i]);
    glLinkProgram(this->program);
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program, 2048, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    for (int i = 0; i < components; i++)
        glDeleteShader(shaders[i]);
}

SunShader::SunShader(std::string vertexPath, std::string geometryPath, std::string fragmentPath, int a) {
    std::string vertexCode = getShaderCodeFromFile(vertexPath);
    std::string geometryCode = getShaderCodeFromFile(geometryPath);
    std::string fragmentCode = getShaderCodeFromFile(fragmentPath);

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

void SunShader::init() {

}

void SunShader::uniforms(SunNode *root) {
	SunAction uniform("uniform");
	uniform.addParameter("shader", this);
	uniform.setRecursive(true);
	sendAction(uniform, root);
}

void SunShader::use() {
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
