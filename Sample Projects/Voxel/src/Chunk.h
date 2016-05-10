// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef CHUNK_H
#define CHUNK_H

#include <Sunglasses/Sunglasses.hpp>

class Chunk : public SunNode {
public:
    void init();

    void update(SunAction action);

    void render(SunAction action);
private:

};

#endif
