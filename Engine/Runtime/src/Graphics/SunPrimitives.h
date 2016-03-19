// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef Sunglasses_SunPrimitives_h
#define Sunglasses_SunPrimitives_h

#include <GL/glew.h>
#include <vector>
#include <map>
#include <list>
#include <random>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

extern bool operator==(const SunVertex &v1, const SunVertex &v2);

struct Simplex {
    glm::vec3 vertices[4];
    int size;
    glm::vec3 &a, &b, &c, &d;

    Simplex() : a(vertices[0]), b(vertices[1]), c(vertices[2]), d(vertices[3]) {
        clear();
    }

    void clear() {
        size = 0;
    }

    void set(glm::vec3 _a, glm::vec3 _b, glm::vec3 _c, glm::vec3 _d) {
        size = 4;
        this->a = _a;
        this->b = _b;
        this->c = _c;
        this->d = _d;
    }

    void set(glm::vec3 _a, glm::vec3 _b, glm::vec3 _c) {
        size = 3;
        this->a = _a;
        this->b = _b;
        this->c = _c;
    }

    void set(glm::vec3 _a, glm::vec3 _b) {
        size = 2;
        this->a = _a;
        this->b = _b;
    }

    void set(glm::vec3 _a) {
        size = 1;
        this->a = _a;
    }

    void add(glm::vec3 point) {
        size = std::min(size + 1, 4);
        for (size_t i = size - 1; i > 0; i--) vertices[i] = vertices[i - 1];
            vertices[0] = point;
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
            for (size_t i = 0; i < width * height; i++) {
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
