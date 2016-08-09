// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.

namespace sunglasses {

/// An entity in the game engine that can be composed of several components
/**
 * This class represents an entity that can be composed of several components.
 * The components may depend on an entity for values, so components have a template
 * parameter that is the type of entity they depend on. A process typically
 * operates on a set of components of the same type, but belong to different
 * entities.
 * @see Component
 * @see Process
 */
class Entity {
public:

private:

};

} // namespace
