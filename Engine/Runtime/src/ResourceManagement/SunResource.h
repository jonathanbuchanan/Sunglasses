// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNRESOURCE_H
#define SUNRESOURCE_H

/// An abstract class used to store resources
/**
 * This is an abstract class that is meant to be subclassed and implement
 * a resource storage object.
 * @warning The constructor should initialize values of the subclass, but it @b cannot
 * do any resource loading. This @b must be done in init().
 * @see SunResourceManager
 * @see SunResourceService
 */
class SunResource {
public:
    /// The pure virtual destructor
    virtual ~SunResource() = 0;

    /// Initializes the resource
    /**
     * This pure virtual member function should load the resource when overridden.
     * @warning Do not implement @b any resource loading functionality in the
     * constructor.
     */
    virtual void init() = 0;
private:

};

#endif
