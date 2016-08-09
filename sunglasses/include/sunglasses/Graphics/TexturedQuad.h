// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef TEXTUREDQUAD_H
#define TEXTUREDQUAD_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include <sunglasses/Graphics/Primitives.h>
#include <sunglasses/Graphics/Shader.h>

namespace sunglasses {

class TexturedQuad : public Base {
public:
    TexturedQuad() { }

    void init();

    void render(Action action);
private:
    // Vertices, indices, and textures
    std::vector<Vertex> vertices = {
        Vertex(glm::vec3(1.0, 1.0, 0.0), glm::vec2(1.0, 1.0)),
        Vertex(glm::vec3(1.0, -1.0, 0.0), glm::vec2(1.0, 0.0)),
        Vertex(glm::vec3(-1.0, -1.0, 0.0), glm::vec2(0.0, 0.0)),
        Vertex(glm::vec3(-1.0, 1.0, 0.0), glm::vec2(0.0, 1.0))
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

} // namespace

#endif
