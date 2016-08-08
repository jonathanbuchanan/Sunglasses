// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Extern/SunResourceService.h>

SunResourceService::SunResourceService() {

}

void SunResourceService::update() {

}

SunResourceManager * SunResourceService::operator[](std::string name) {
    if (resourceManagers.find(name) == resourceManagers.end())
        return nullptr; // Resource manager is not present, return -1
    return resourceManagers[name].get();
}

SunResourceManager * SunResourceService::getResourceManager(std::string name) {
    if (resourceManagers.find(name) == resourceManagers.end())
        return nullptr; // Resource manager is not present, return -1
    return resourceManagers[name].get();
}

int SunResourceService::addResourceManager(std::string name, SunResourceManager *manager) {
    if (resourceManagers.find(name) != resourceManagers.end())
        return -1; // Resource manager is already existant, return -1
    else
        resourceManagers[name] = std::unique_ptr<SunResourceManager>(manager);
    return 0;
}

int SunResourceService::removeResourceManager(std::string name) {
    if (resourceManagers.find(name) == resourceManagers.end())
        return -1; // Resource manager is not present, return -1
    resourceManagers.erase(name);
    return 0;
}
