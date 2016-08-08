// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNDIRECTIONALLIGHT_H
#define SUNDIRECTIONALLIGHT_H

#include "../Core/SunNode.h"

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace sunglasses {

/// A node intended to be used as a directional light in the scene graph
/**
 * This subclass of SunNode is intended to be used as a directional light. A
 * directional light has a color and a direction. All of its rays are parallel
 * so it has no position.
 */
class SunDirectionalLight : public SunNode {
public:
    /// A constructor
    SunDirectionalLight();

    /// A constructor
    /**
     * @param _color The color of the directional light
     * @param _direction The direction of the directional light
     */
    SunDirectionalLight(glm::vec3 _color, glm::vec3 _direction);

    /// Initializes the directional light.
    virtual void init();

    /// Updates the directional light.
    virtual void update(SunAction action);

    /// Passes the uniforms to a shader (color and direction).
    virtual void uniform(SunAction action);

    /// Sets the color of the directional light.
    void setColor(glm::vec3 _color) { color = _color; }

    /// Sets the direction of the directional light.
    void setDirection(glm::vec3 _direction) { direction = _direction; }
protected:
    /// The color of the directional light
    glm::vec3 color;

    /// The direction of the directional light
    glm::vec3 direction;
};

} // namespace

#endif
