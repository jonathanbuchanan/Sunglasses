// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIPATH_H
#define SUNGUIPATH_H

#include <array>
#include <functional>

#include <glm/glm.hpp>

class SunGUIPathComponent;

/// A path in the GUI API. Can be filled or stroked.
/**
 * A path is a a sequence of connected lines and curves. A path can
 * be filled or stroked. The components of a path are represented
 * as a tuple, so the template parameters of this class are
 * the components in the path. A component is an instruction
 * for how to construct the path, which is not necessarily
 * a physical object.
 */
template<int N>
class SunGUIPath {
public:
    /// Constructs a path from the given components
    template<typename... T>
    SunGUIPath(const T &... _components) : components{std::ref((const SunGUIPathComponent &)_components)...} { }
private:
    /// The array of components to the path
    std::array<const std::reference_wrapper<const SunGUIPathComponent>, N> components;
};

/// A component in a path
class SunGUIPathComponent {
public:
    virtual void tessellate() = 0;
};

/// A line component in a path
class SunGUIPathLine : SunGUIPathComponent {
public:
    /// Constructs the line from two points
    SunGUIPathLine(glm::ivec2 _a, glm::ivec2 _b);

    virtual void tessellate();
private:
    /// The two points defining the line
    glm::ivec2 a, b;
};

#endif
