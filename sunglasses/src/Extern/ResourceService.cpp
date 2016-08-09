// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Extern/ResourceService.h>

namespace sunglasses {

ResourceService::ResourceService() {

}

void ResourceService::update() {

}

ResourceManager * ResourceService::operator[](std::string name) {
    if (resourceManagers.find(name) == resourceManagers.end())
        return nullptr; // Resource manager is not present, return -1
    return resourceManagers[name].get();
}

ResourceManager * ResourceService::getResourceManager(std::string name) {
    if (resourceManagers.find(name) == resourceManagers.end())
        return nullptr; // Resource manager is not present, return -1
    return resourceManagers[name].get();
}

int ResourceService::addResourceManager(std::string name, ResourceManager *manager) {
    if (resourceManagers.find(name) != resourceManagers.end())
        return -1; // Resource manager is already existant, return -1
    else
        resourceManagers[name] = std::unique_ptr<ResourceManager>(manager);
    return 0;
}

int ResourceService::removeResourceManager(std::string name) {
    if (resourceManagers.find(name) == resourceManagers.end())
        return -1; // Resource manager is not present, return -1
    resourceManagers.erase(name);
    return 0;
}

} // sunglasses
