// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

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

extern std::uniform_real_distribution<GLfloat> randomFloats;
extern std::default_random_engine generator;

namespace sunglasses {

// Vertex Declaration
struct Vertex {
    // Position, normal, and texture coordinates
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec2 textureCoordinates;
    GLuint boneIDs[4];
    GLfloat boneWeights[4];

    Vertex() {

    }

    Vertex(glm::vec3 _position) {
        position = _position;
    }

    Vertex(glm::vec3 _position, glm::vec2 _textureCoordinates) {
        position = _position;
        textureCoordinates = _textureCoordinates;
    }
};

extern bool operator==(const Vertex &v1, const Vertex &v2);

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

// Bone Declaration
struct Bone {
    std::string name;
    GLint parentID;

    glm::mat4 relativeTransform;
    glm::mat4 globalTransform;
    glm::mat4 bindPose;
    glm::mat4 inverseBindPose;
};

// AnimationChannel Declaration
struct AnimationChannel {
    GLuint boneID;

    std::vector<GLdouble> rotationKeyTicks;
    std::vector<glm::quat> rotationKeyValues;
};

// Animation Declaration
struct Animation {
    GLdouble length;
    GLdouble ticksPerSecond;

    std::vector<AnimationChannel> channels;
};

enum TextureType {
    TextureTypeImage,
    TextureTypeNoiseFloat,
    TextureTypeNoiseVec2,
    TextureTypeNoiseVec3,
    TextureTypeNoiseHemisphere
};

typedef GLuint FramebufferObject;
typedef GLuint FramebufferTextureObject;
typedef GLuint FramebufferColorAttachmentObject;

struct Framebuffer {
    GLuint framebuffer;
    GLuint renderbuffer;
    std::vector<FramebufferColorAttachmentObject> colorAttachments;
    std::map<std::string, FramebufferTextureObject> textures;
};

typedef std::map<std::string, FramebufferTextureObject>::iterator FramebufferTextureObjectIterator;

extern void clear();

} // namespace

#endif
