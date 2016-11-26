// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef ENTITY_H
#define ENTITY_H

#include <tuple>

namespace sunglasses {

/// An entity in the game engine that can be composed of several components
/**
 * A game object that is composed of several components. Components
 * may not contain any logic themselves, but can be operated on
 * by processes.
 * @see Component
 * @see Process
 */
template<typename... Cs>
class Entity {
public:
    /// Returns references to the specified components
    template<typename... Ts>
    std::tuple<Ts &...> getComponents() {
        return std::make_tuple(std::get<Ts &>(components)...);
    }
private:
    /// The tuple of references to components
    std::tuple<Cs &...> components;
};

} // namespace

#endif
