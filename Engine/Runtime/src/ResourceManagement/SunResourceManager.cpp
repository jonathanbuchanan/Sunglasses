// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunResourceManager.h"

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
