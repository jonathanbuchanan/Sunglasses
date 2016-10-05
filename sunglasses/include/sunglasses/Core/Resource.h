#ifndef RESOURCE_H
#define RESOURCE_H

namespace sunglasses {

/// A pure virtual class that represents a resource in a resource library
/**
 * An associated 'parameters' class should exist to accompany the resource.
 * This should contain the data necessary to load the resource without any other input.
 */
class Resource {
public:

private:

};

/// A pure virtual class that represents a resource in a resource library holding other resources
/**
 * The MultiResource class is a resource that, in addition to its own data,
 * contributes additional resources to other types of resource libraries.
 */
template<typename... T>
class MultiResource {
public:

private:

};

} // namespace

#endif
