// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "Chunk.h"

#include "Block.h"

void Chunk::init() {
    addAction("render", &Chunk::render);
    addAction("update", &Chunk::update);

    std::shared_ptr<Block> block = std::make_shared<Block>();
    block->init();
    addSubNode(block);

    std::shared_ptr<Block> block2 = std::make_shared<Block>();
    block2->init();
    block2->setPosition(glm::vec3(0.0f, -5.0f, 0.0f));
    addSubNode(block2);
}

void Chunk::update(SunAction action) {

}

void Chunk::render(SunAction action) {

}
