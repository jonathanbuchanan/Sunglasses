#include "Block.h"

void Block::init() {
    addAction("update", &Block::update);
    addAction("render", &Block::render);

    std::map<std::string, SunResource *> meshMap;

    SunResourceService *resource = services->get<SunResourceService>();
    resource->getResourceManager("models")->addResource("cube", new SunModelResource("res/Graphics/Models/Cube.dae", &meshMap));
    resource->getResourceManager("meshes")->addResources(meshMap);
    meshMap.clear();

    resource->getResourceManager("textures")->addResource("grass", new SunTextureResource("res/Graphics/Textures/grass.png"));

    SunTextureResource *grassTexture = (SunTextureResource *)resource->getResourceManager("textures")->getResource("grass");

    resource->getResourceManager("materials")->addResource("grass", new SunMaterialResource(grassTexture, 4.0f));

    addTag("textured");

    newMesh("cube", "Cube", "grass");

    SunObject::init();
}

void Block::update(SunAction action) {

}

void Block::render(SunAction action) {
    SunObject::render(action);
}
