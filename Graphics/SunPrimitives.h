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
#include <vector>
#include <map>
#include <random>
#include "../Libraries/glm/glm.hpp"
#include "../Libraries/glm/gtc/matrix_transform.hpp"
#include "../Libraries/glm/gtc/quaternion.hpp"
#include "../Libraries/glm/gtx/quaternion.hpp"
#include "../Libraries/glm/gtx/string_cast.hpp"
#include "../Libraries/assimp/Importer.hpp"
#include "../Libraries/assimp/scene.h"
#include "../Libraries/assimp/postprocess.h"

using namespace std;

extern uniform_real_distribution<GLfloat> randomFloats;
extern default_random_engine generator;

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

enum SunTextureType {
    SunTextureTypeImage,
    SunTextureTypeNoiseFloat,
    SunTextureTypeNoiseVec2,
    SunTextureTypeNoiseVec3,
    SunTextureTypeNoiseHemisphere
};

// SunTexture Declaration
struct SunTexture {
    // ID, type, and path
    GLuint id;
    string name;
    aiString path;
    GLuint width;
    GLuint height;
    SunTextureType type;
    
    SunTexture() {
        
    }
    
    SunTexture(GLuint _width, GLuint _height, SunTextureType _type) {
        width = _width;
        height = _height;
        type = _type;
        
        generate();
    }
    
    void generate() {
        if (type == SunTextureTypeNoiseHemisphere) {
            vector<glm::vec3> noise;
            for (int i = 0; i < width * height; i++) {
                glm::vec3 value = glm::vec3(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, 0.0);
                noise.push_back(value);
            }
            
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, &noise[0]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
        }
    }
    
};

typedef GLuint SunFramebufferObject;
typedef GLuint SunFramebufferTextureObject;
typedef GLuint SunFramebufferColorAttachmentObject;

struct SunFramebuffer {
    GLuint framebuffer;
    GLuint renderbuffer;
    vector<SunFramebufferColorAttachmentObject> colorAttachments;
    map<string, SunFramebufferTextureObject> textures;
};

typedef map<string, SunFramebufferTextureObject>::iterator SunFramebufferTextureObjectIterator;

extern void clear();

#endif
