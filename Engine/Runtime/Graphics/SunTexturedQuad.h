// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef Sunglasses_SunTexturedQuad_h
#define Sunglasses_SunTexturedQuad_h

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include "./SunPrimitives.h"
#include "Graphics/SunShader.h"

typedef map<string, pair<GLuint, GLuint>>::iterator SunTextureMapIterator;

class SunTexturedQuad {
public:
    SunTexturedQuad() { }
    
    void setUpGL();
    void render(map<string, pair<GLuint, GLuint>> _textures, SunShader _shader);
    void renderWithUsedShader(map<string, pair<GLuint, GLuint>> _textures, SunShader _shader);
    
    inline vector<SunVertex> & getVertices() { return vertices; }
    inline vector<GLuint> & getIndices() { return indices; }
    
    inline GLuint & getVBO() { return VBO; }
    inline GLuint & getEBO() { return EBO; }
    inline GLuint & getVAO() { return VAO; }
private:
    // Vertices, indices, and textures
    vector<SunVertex> vertices = {
        SunVertex(glm::vec3(1.0, 1.0, 0.0), glm::vec2(1.0, 1.0)),
        SunVertex(glm::vec3(1.0, -1.0, 0.0), glm::vec2(1.0, 0.0)),
        SunVertex(glm::vec3(-1.0, -1.0, 0.0), glm::vec2(0.0, 0.0)),
        SunVertex(glm::vec3(-1.0, 1.0, 0.0), glm::vec2(0.0, 1.0))
    };
    vector<GLuint> indices = {
        0, 1, 2,
        2, 3, 0
    };

    // VBO, EBO, and VAO
    GLuint VBO;
    GLuint EBO;
    GLuint VAO;
};

#endif
