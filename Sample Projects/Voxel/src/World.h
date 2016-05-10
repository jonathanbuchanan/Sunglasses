// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef WORLD_H
#define WORLD_H

#include <Sunglasses/Sunglasses.hpp>

#include "Chunk.h"

class World : public SunNode {
public:
    void init();

    void update(SunAction action);
private:
    std::vector<Chunk> chunks;
};

#endif
