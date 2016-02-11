// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNBASE_H
#define SUNBASE_H

#include <string>
#include <map>

#include "SunService.h"

class SunBase {
public:
    
    inline std::string & getName() { return name; }
    inline void setName(std::string n) { name = n; }
    
    inline std::map<std::string, SunService *> & getServices() { return services; }
    inline void addService(SunService *s) { services[s->name] = s; }
private:
    std::string name;
    static std::map<std::string, SunService *> services;
};

#endif