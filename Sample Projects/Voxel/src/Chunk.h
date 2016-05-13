// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef CHUNK_H
#define CHUNK_H

#include <Sunglasses/Sunglasses.hpp>

#include "Block.h"

class Chunk : public SunNode {
public:
    void init();

    void update(SunAction action);

    void render(SunAction action);
private:
    /// Generates a mesh from the blocks that it contains
    void generateMesh();

    GLuint VBO;
    GLuint EBO;
    GLuint VAO;

    std::vector<SunVertex> vertices;
    std::vector<GLuint> indices;

    Block *blocks[16][128][16];
};

#endif
