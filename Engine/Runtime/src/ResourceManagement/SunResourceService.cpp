// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunResourceService.h"

SunResourceService::SunResourceService() {

}

void SunResourceService::update() {
    
}

SunResourceManager * SunResourceService::operator[](std::string name) {
    return resourceManagers[name].get();
}

SunResourceManager * SunResourceService::getResourceManager(std::string name) {
    return resourceManagers[name].get();
}

int SunResourceService::addResourceManager(std::string name, SunResourceManager *manager) {

}
