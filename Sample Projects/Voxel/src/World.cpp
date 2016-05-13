// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "World.h"

void World::init() {
    addAction("update", &World::update);

    std::map<std::string, SunResource *> meshMap;

    SunResourceService *resource = services->get<SunResourceService>();
    resource->getResourceManager("models")->addResource("cube", new SunModelResource("res/Graphics/Models/Cube.dae", &meshMap));
    resource->getResourceManager("meshes")->addResources(meshMap);
    meshMap.clear();

    resource->getResourceManager("textures")->addResource("grass", new SunTextureResource("res/Graphics/Textures/grass.png"));

    SunTextureResource *grassTexture = (SunTextureResource *)resource->getResourceManager("textures")->getResource("grass");

    resource->getResourceManager("materials")->addResource("grass", new SunMaterialResource(grassTexture, 4.0f));

    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
    chunk->init();
    addSubNode(chunk);

    std::shared_ptr<SunShadowDirectionalLight> _dir = std::shared_ptr<SunShadowDirectionalLight>(new SunShadowDirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, -1.0f, 0.6f)));
    _dir->setResolution(glm::ivec2(4096, 4096));
    _dir->setDistance(40.0f);
    _dir->setSize(glm::vec2(35.0f, 35.0f));
    _dir->setTarget(this);
    _dir->addTag("shadow_directional_light");
    _dir->init();
    addSubNode(_dir);
}

void World::update(SunAction action) {

} 
