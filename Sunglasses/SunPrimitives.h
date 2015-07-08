//
//  SunPrimitives.h
//  Sunglasses
//
//  Created by Jonathan Buchanan on 7/7/15.
//
//

#ifndef Sunglasses_SunPrimitives_h
#define Sunglasses_SunPrimitives_h

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"

// SunVertex Declaration
struct SunVertex {
    // Position, normal, and texture coordinates
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec2 textureCoordinates;
    GLuint boneIDs[4];
    GLfloat boneWeights[4];
    
    SunVertex() {
        
    }
    
    SunVertex(glm::vec3 _position) {
        position = _position;
    }
    
    SunVertex(glm::vec3 _position, glm::vec2 _textureCoordinates) {
        position = _position;
        textureCoordinates = _textureCoordinates;
    }
};

// SunBone Declaration
struct SunBone {
    string name;
    GLint parentID;
    
    glm::mat4 relativeTransform;
    glm::mat4 globalTransform;
    glm::mat4 bindPose;
    glm::mat4 inverseBindPose;
};

// SunAnimationChannel Declaration
struct SunAnimationChannel {
    GLuint boneID;
    
    vector<GLdouble> rotationKeyTicks;
    vector<glm::quat> rotationKeyValues;
};

// SunAnimation Declaration
struct SunAnimation {
    GLdouble length;
    GLdouble ticksPerSecond;
    
    vector<SunAnimationChannel> channels;
};

// SunTexture Declaration
struct SunTexture {
    // ID, type, and path
    GLuint id;
    string type;
    aiString path;
};

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

#endif
