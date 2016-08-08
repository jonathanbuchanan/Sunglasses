// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Extern/SunResourceManager.h>

namespace sunglasses {

SunResourceManager::SunResourceManager() {

}

int SunResourceManager::addResource(std::string name, SunResource *resource) {
    if (resources.find(name) != resources.end())
        return -1; // Resource is already existant, return -1
    else {
        resources[name] = std::unique_ptr<SunResource>(resource);
        resources[name]->init();
    }
    return 0;
}

int SunResourceManager::addResources(std::map<std::string, SunResource *> &_resources) {
    bool perfect = true;
    for (auto &iterator : _resources) {
        if (resources.find(iterator.first) != resources.end()) {
            perfect = false;
        } else {
            resources[iterator.first] = std::unique_ptr<SunResource>(iterator.second);
            resources[iterator.first]->init();
        }
    }
    if (perfect)
        return 0;
    else
        return -1;
}

SunResource * SunResourceManager::getResource(std::string name) {
    if (resources.find(name) == resources.end())
        return nullptr; // Resource is not present, return -1
    return resources[name].get();
}

SunResource * SunResourceManager::operator[](std::string name) {
    if (resources.find(name) == resources.end())
        return nullptr; // Resource is not present, return -1
    return resources[name].get();
}

int SunResourceManager::removeResource(std::string name) {
    if (resources.find(name) == resources.end())
        return -1; // Resource is not present, return -1
    resources.erase(name);
    return 0;
}

} // namespace
