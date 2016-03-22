// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNTEXTUREDQUAD_H
#define SUNTEXTUREDQUAD_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include "SunPrimitives.h"
#include "SunShader.h"

typedef std::map<std::string, std::pair<GLuint, GLuint>>::iterator SunTextureMapIterator;

class SunTexturedQuad {
public:
    SunTexturedQuad() { }

    void setUpGL();
    void render(std::map<std::string, std::pair<GLuint, GLuint>> _textures, SunShader _shader);
    void renderWithUsedShader(std::map<std::string, std::pair<GLuint, GLuint>> _textures, SunShader _shader);
private:
    // Vertices, indices, and textures
    std::vector<SunVertex> vertices = {
        SunVertex(glm::vec3(1.0, 1.0, 0.0), glm::vec2(1.0, 1.0)),
        SunVertex(glm::vec3(1.0, -1.0, 0.0), glm::vec2(1.0, 0.0)),
        SunVertex(glm::vec3(-1.0, -1.0, 0.0), glm::vec2(0.0, 0.0)),
        SunVertex(glm::vec3(-1.0, 1.0, 0.0), glm::vec2(0.0, 1.0))
    };
    std::vector<GLuint> indices = {
        0, 1, 2,
        2, 3, 0
    };

    // VBO, EBO, and VAO
    GLuint VBO;
    GLuint EBO;
    GLuint VAO;
};

#endif
