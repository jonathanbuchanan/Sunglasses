// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Extern/ResourceManager.h>

namespace sunglasses {

ResourceManager::ResourceManager() {

}

int ResourceManager::addResource(std::string name, Resource *resource) {
    if (resources.find(name) != resources.end())
        return -1; // Resource is already existant, return -1
    else {
        resources[name] = std::unique_ptr<Resource>(resource);
        resources[name]->init();
    }
    return 0;
}

int ResourceManager::addResources(std::map<std::string, Resource *> &_resources) {
    bool perfect = true;
    for (auto &iterator : _resources) {
        if (resources.find(iterator.first) != resources.end()) {
            perfect = false;
        } else {
            resources[iterator.first] = std::unique_ptr<Resource>(iterator.second);
            resources[iterator.first]->init();
        }
    }
    if (perfect)
        return 0;
    else
        return -1;
}

Resource * ResourceManager::getResource(std::string name) {
    if (resources.find(name) == resources.end())
        return nullptr; // Resource is not present, return -1
    return resources[name].get();
}

Resource * ResourceManager::operator[](std::string name) {
    if (resources.find(name) == resources.end())
        return nullptr; // Resource is not present, return -1
    return resources[name].get();
}

int ResourceManager::removeResource(std::string name) {
    if (resources.find(name) == resources.end())
        return -1; // Resource is not present, return -1
    resources.erase(name);
    return 0;
}

} // namespace
