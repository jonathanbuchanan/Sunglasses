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
#include "../Libraries/glm/glm.hpp"
#include "../Libraries/glm/gtc/matrix_transform.hpp"
#include "../Libraries/glm/gtc/quaternion.hpp"
#include "../Libraries/glm/gtx/quaternion.hpp"
#include "../Libraries/glm/gtx/string_cast.hpp"

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

void clear() {
    // Clear the scene using this color
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

#endif
