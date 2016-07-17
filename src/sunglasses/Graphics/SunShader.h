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

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <sunglasses/Core/SunNode.h>
#include <sunglasses/Output/SunLogger.h>

enum SunShaderSourceType {
    SunShaderSourceTypeVertex = GL_VERTEX_SHADER,
    SunShaderSourceTypeFragment = GL_FRAGMENT_SHADER,
    SunShaderSourceTypeGeometry = GL_GEOMETRY_SHADER
};

extern std::string getShaderCodeFromFile(std::string filepath);
extern GLuint compileShaderFromString(std::string shaderString, GLint shaderType);

class SunShader : public SunBase {
    class SunShaderUniform;
public:
    /// Constructs the shader from a vertex and fragment shader
    SunShader(const std::string &vertex, const std::string &fragment);

    /// Constructs the shader from a list of sources
    /**
     * This constructor loads the shader from the list of shaders. Each element
     * in the sources vector is a pair. The first part of the pair is the path
     * to the shader source, and the second part of the pair is an enum identifying
     * the type of shader (vertex, fragment, geometry, etc.).
     * @param sources The vector of sources
     */
    SunShader(std::vector<std::pair<std::string, SunShaderSourceType>> sources);

    /// Accesses the uniform at the given name
    /**
     * @warning The shader must be currently active to use this method correctly
     */
    SunShaderUniform operator[](std::string uniform);

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

    /// Returns the next texture unit.
    /**
     * This method returns the next available texture unit for use in glActiveTexture().
     * It also increments the usedTextureUnits member.
     * @return The next available texture unit
     */
    int getNextTextureUnit();

    /// Returns the size of an array in the shader.
    /**
     * This method is useful when populating an array in the shader.
     * @see getNextArrayIndex()
     * @param array The name of the array
     */
    int getArraySize(std::string array);

    GLuint getProgram() { return program; }
private:
    /// A struct used to represent a uniform
    class SunShaderUniform {
    public:
        /// Constructs the uniform object from a shader program and a uniform index
        SunShaderUniform(GLuint _program, GLuint _index);

        /// Assigns a float
        void operator=(GLfloat value);

        /// Assigns a double
        void operator=(GLdouble value);

        /// Assigns a vec2
        void operator=(glm::vec2 value);

        /// Assigns a vec3
        void operator=(glm::vec3 value);

        /// Assigns a vec4
        void operator=(glm::vec4 value);


        /// Assigns an integer
        void operator=(GLint value);

        /// Assigns a boolean
        void operator=(GLboolean value);

        /// Assigns an ivec2
        void operator=(glm::ivec2 value);

        /// Assigns an ivec3
        void operator=(glm::ivec3 value);

        /// Assigns an ivec4
        void operator=(glm::ivec4 value);


        /// Assigns an unsigned integer
        void operator=(GLuint value);

        /// Assigns a uvec2
        void operator=(glm::uvec2 value);

        /// Assigns a uvec3
        void operator=(glm::uvec3 value);

        /// Assigns a uvec4
        void operator=(glm::uvec4 value);


        /// Assigns a mat2
        void operator=(glm::mat2 value);

        /// Assigns a mat3
        void operator=(glm::mat3 value);

        /// Assigns a mat4
        void operator=(glm::mat4 value);


        /// Assigns a mat2x3
        void operator=(glm::mat2x3 value);

        /// Assigns a mat3x2
        void operator=(glm::mat3x2 value);

        /// Assigns a mat2x4
        void operator=(glm::mat2x4 value);

        /// Assigns a mat4x2
        void operator=(glm::mat4x2 value);

        /// Assigns a mat3x4
        void operator=(glm::mat3x4 value);

        /// Assigns a mat4x3
        void operator=(glm::mat4x3 value);
    private:
        /// The shader program
        GLuint program;

        /// The index of the uniform within the program
        GLuint index;
    };

    /// The map of arrays
    std::map<std::string, int> arrays;

    /// The number of used texture units
    /**
     * This member is used to get the next available texture unit during rendering.
     * Use getNextTextureUnit() to get the next texture unit. Pass the returned value
     * plus GL_TEXTURE0
     * to glActiveTexture(). This value is reset when use() is called.
     */
    int usedTextureUnits = 0;

    /// The program in the OpenGL context
    GLuint program;
};

#endif
