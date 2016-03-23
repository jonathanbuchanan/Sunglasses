// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNRESOURCEMANAGER_H
#define SUNRESOURCEMANAGER_H

#include "SunResource.h"

#include <map>
#include <string>
#include <memory>

/// This object provides dynamic access to a set of resources
/**
 * This object is designed to give access to a map of resources. It only loads
 * resources when necessary, to avoid duplicating resources and doing extra
 * work.
 */
class SunResourceManager {
public:
    SunResourceManager();

    /// Adds a resource
    /**
     * This function adds a resource to the map. It is reccomended that
     * you only construct the resource because the service takes control
     * after that.
     * @param name The name of the resource
     * @param resource A pointer to the resource
     * @retval 0 The function executed successfully
     * @retval -1 The function did not execute successfully (probably an item already had the same spot)
     */
    int addResource(std::string name, SunResource *resource);

    /// Gets a pointer to the associated resource
    /**
     * Returns a pointer found in the map in exchange for the name.
     * @param name The name of the resource to be searched for
     * @return A pointer to the requested resource
     * @retval nullptr The requested resource could not be found
     */
    SunResource * getResource(std::string name);

    /// Gets a pointer to the associated resource
    /**
     * Returns a pointer found in the map in exchange for the name.
     * @param name The name of the resource to be searched for
     * @return A pointer to the requested resource
     * @retval nullptr The requested resource could not be found
     */
    SunResource * operator[](std::string name);

    /// Removes a resource
    /**
     * This function removes a resource from the map.
     * @param name The name of the resource to be removed
     * @retval 0 The function executed successfully
     * @retval -1 The function did not execute successfully (probably the item did not exist in the map)
     */
    int removeResource(std::string name);
private:
    /// The map of resources (strings are keys)
    std::map<std::string, std::unique_ptr<SunResource>> resources;

};

#endif
