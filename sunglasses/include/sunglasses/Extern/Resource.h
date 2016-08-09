// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef RESOURCE_H
#define RESOURCE_H

namespace sunglasses {

/// An abstract class used to store resources
/**
 * This is an abstract class that is meant to be subclassed and implement
 * a resource storage object.
 * @warning The constructor should initialize values of the subclass, but it @b cannot
 * do any resource loading. This @b must be done in init().
 * @see ResourceManager
 * @see ResourceService
 */
class Resource {
public:
    /// The pure virtual destructor
    virtual ~Resource() = 0;

    /// Initializes the resource
    /**
     * This pure virtual member function should load the resource when overridden.
     * @warning Do not implement @b any resource loading functionality in the
     * constructor.
     */
    virtual void init() = 0;
private:

};

} // namespace

#endif
