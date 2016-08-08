// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNPOINTLIGHTOBJECT_H
#define SUNPOINTLIGHTOBJECT_H

#include "../Core/SunNode.h"

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace sunglasses {

/// A node intended to be used as a point light in the scene graph
/**
 * This subclass of SunNode is intended to be used as a point light. A
 * point light has a color and position, and its light attenuates, meaning that
 * the light gets less intense as you go farther away.
 */
class SunPointLight : public SunNode {
public:
    /// A constructor
    SunPointLight();

    /// A constructor
    /**
     * @param _color The color of the new point light
     * @param _position The position of the new point light
     */
    SunPointLight(glm::vec3 _color, glm::vec3 _position);

    /// Initializes the point light.
    virtual void init();

    /// Updates the point light.
    virtual void update(SunAction action);

    /// Passes the uniforms to a shader (color and position).
    virtual void uniform(SunAction action);

    /// Sets the color of the point light.
    void setColor(glm::vec3 _color) { color = _color; }

    /// Sets the position of the point light.
    void setPosition(glm::vec3 _position) { position = _position; }
protected:
    /// The color of the point light
    glm::vec3 color;

    /// The position of the point light
    glm::vec3 position;
};

} // namespace

#endif
