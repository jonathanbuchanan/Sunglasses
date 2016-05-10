// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "World.h"

void World::init() {
    addAction("update", &World::update);

    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
    chunk->init();
    addSubNode(chunk);

    std::shared_ptr<SunShadowDirectionalLight> _dir = std::shared_ptr<SunShadowDirectionalLight>(new SunShadowDirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, -1.0f, 0.6f)));
    _dir->setResolution(glm::ivec2(4096, 4096));
    _dir->setDistance(10.0f);
    _dir->setTarget(this);
    _dir->addTag("shadow_directional_light");
    _dir->init();
    addSubNode(_dir);
}

void World::update(SunAction action) {

} 
