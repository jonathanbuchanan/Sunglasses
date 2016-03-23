// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNRESOURCEMANAGER_H
#define SUNRESOURCEMANAGER_H

#include "SunResource.h"

#include <string>

class SunResourceManager {
public:
    SunResourceManager();

    int addResource(std::string name, SunResource *resource);

    SunResource * getResource(std::string name);

    SunResource * operator[](std::string name);

    int removeResource(std::string name);
private:

};

#endif
