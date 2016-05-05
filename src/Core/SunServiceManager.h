// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNSERVICEMANAGER_H
#define SUNSERVICEMANAGER_H
#include <map>
#include <typeindex>
#include <memory>

#include "SunService.h"

/// A class that manages a map of services with types as keys
/**
 * This class manages a map of services with types as keys. This
 * can be easily passed around, or shared as a static member.
 */
class SunServiceManager {
public:
    /// Accesses a service from the type given in the template parameter.
    template<typename T>
    T * get() {
        return (T *)(services[std::type_index(typeid(T))]).get();
    }

    /// Adds a service from the pointer passed.
    /**
     * @param service A pointer to the service to add
     */
    template<typename T>
    void add(T *service) {
        services[std::type_index(typeid(T))] = std::unique_ptr<SunService>(service);
    }

    std::map<std::type_index, std::unique_ptr<SunService>> & getServices() {
        return services;
    }
private:
    /// The map of services
    std::map<std::type_index, std::unique_ptr<SunService>> services;
};

#endif
