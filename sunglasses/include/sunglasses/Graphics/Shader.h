// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <sunglasses/Core/Node.h>
#include <sunglasses/Output/Logger.h>

namespace sunglasses {

class Texture;

enum ShaderSourceType {
    ShaderSourceTypeVertex = GL_VERTEX_SHADER,
    ShaderSourceTypeFragment = GL_FRAGMENT_SHADER,
    ShaderSourceTypeGeometry = GL_GEOMETRY_SHADER
};

// TODO: Remove these two functions
extern std::string getShaderCodeFromFile(std::string filepath);
extern GLuint compileShaderFromString(std::string shaderString, GLint shaderType);

class Shader {
    class ShaderUniform;

    /// A class that represents a texture unit
    /**
     * This class is used to control a single texture unit in OpenGL.
     * It may be assigned a texture object using the assignment operator,
     * setting the value of the uniform.
     */
    class TextureUnit {
    public:
        /// Constructs the texture unit with a unit number
        TextureUnit(GLuint _unit, GLuint _program, std::string _name);

        /// Assigns a texture to the unit (and sets a uniform)
        void operator=(const Texture &texture);
    private:
        /// The texture uniform number
        /**
         * @warning Do not add GL_TEXTURE0 to this. This happens automatically.
         */
        GLuint unit;

        /// The shader program
        GLuint program;

        /// The name of the texture
        /**
         * This is used to look up the uniform in the shader.
         */
        std::string name;
    };

    /// A class that maps texture names to sampler uniforms in the shader
    class TextureMapper {
    public:
        /// Constructs a texture mapper from a list of uniform names
        /**
         * This constructor builds the map by iterating through the list
         * and creating a texture unit corresponding to the current
         * index of the list while iterating.
         */
        TextureMapper(GLuint program, std::initializer_list<std::string> textureList);

        /// Returns a texture unit object
        TextureUnit operator[](std::string textureName);
    private:
        /// The map of texture units with names as keys
        std::unordered_map<std::string, TextureUnit> textureUnits;
    };
public:
    /// Constructs the shader from a vertex and fragment shader
    Shader(const std::string &vertex, const std::string &fragment,
        std::initializer_list<std::string> _textures = {});

    /// Constructs the shader from a list of sources
    /**
     * This constructor loads the shader from the list of shaders. Each element
     * in the sources vector is a pair. The first part of the pair is the path
     * to the shader source, and the second part of the pair is an enum identifying
     * the type of shader (vertex, fragment, geometry, etc.).
     * @param sources The vector of sources
     */
    Shader(std::vector<std::pair<std::string, ShaderSourceType>> sources,
        std::initializer_list<std::string> _textures = {});

    /// Destructs the shader by destroying the program
    ~Shader();

    /// Accesses the uniform at the given name
    /**
     * @warning The shader must be currently active to use this method correctly
     */
    ShaderUniform operator[](std::string uniform);

    /// The texture mapper
    /**
     * This object is used to assign textures to texture units. Each texture
     * unit has a name corresponding to the name of the sampler uniform
     * in the shader. Example:
     * @code
     * shader.textures["uniformName"] = texture;
     * @endcode
     */
    TextureMapper textures;

    void uniforms(Node *root);

    void use();
    void use(std::string tag, float delta, Node *root);
    void send(std::string tag, float delta, Node *root);

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
private:
    /// A struct used to represent a uniform
    class ShaderUniform {
    public:
        /// Constructs the uniform object from a shader program and a uniform index
        ShaderUniform(GLuint _program, GLuint _index);

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

    /// The program in the OpenGL context
    GLuint program;
};

} // namespace

#endif
