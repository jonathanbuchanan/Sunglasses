// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNRESOURCESERVICE_H
#define SUNRESOURCESERVICE_H

#include "../Core/SunService.h"
#include "SunResourceManager.h"

#include <map>
#include <string>
#include <memory>

/// This service provides access to a set of resource managers
/**
 * This subclass of SunService is designed to give access to an map of
 * SunResourceManager to all objects that load resources. Using this
 * it makes it easy to access resources and avoid loading duplicates.
 */
class SunResourceService : public SunService {
public:
    /// The default constructor
    SunResourceService();

    void update();

    /// Gets a pointer to the associated resource manager
    /**
     * Returns a pointer found in the map in exchange for the name.
     * @param name The name of the resource manager to be searched for
     * @return A pointer to the requested resource manager
     * @retval nullptr The requested resource manager could not be found
     */
    SunResourceManager * operator[](std::string name);

    /// Gets a pointer to the associated resource manager
    /**
     * Returns a pointer found in the map in exchange for the name.
     * @param name The name of the resource manager to be searched for
     * @return A pointer to the requested resource manager
     * @retval nullptr The requested resource manager could not be found
     */
    SunResourceManager * getResourceManager(std::string name);

    /// Adds a resource manager
    /**
     * This function adds a resource manager to the map. It is reccomended that
     * you only initialize the resource manager because the service takes control
     * after that.
     * @param name The name of the resource manager
     * @param manager A pointer to the resource manager
     * @retval 0 The function executed successfully
     * @retval -1 The function did not execute successfully (probably an item already had the same spot)
     */
    int addResourceManager(std::string name, SunResourceManager *manager);

    /// Removes a resource manager
    /**
     * This function removes a resource manager from the map.
     * @param name The name of the resource manager to be removed
     * @retval 0 The function executed successfully
     * @retval -1 The function did not execute successfully (probably the item did not exist in the map)
     */
    int removeResourceManager(std::string name);
private:
    /// The map of resource managers (strings are keys)
    std::map<std::string, std::unique_ptr<SunResourceManager>> resourceManagers;
};

#endif
