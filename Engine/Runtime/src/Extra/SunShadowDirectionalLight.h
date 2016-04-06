// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNSHADOWDIRECTIONALLIGHT_H
#define SUNSHADOWDIRECTIONALLIGHT_H

#include "SunDirectionalLight.h"

class SunShadowDirectionalLight : public SunDirectionalLight {
public:
    /// A constructor
    SunShadowDirectionalLight();

    /// A constructor
    /**
     * @param _color The color of the directional light
     * @param _direction The direction of the directional light
     */
    SunShadowDirectionalLight(glm::vec3 _color, glm::vec3 _direction);

    /// Initializes the light.
    virtual void init();

    /// Renders the shadow map.
    virtual void shadowMap(SunAction action);

    /// Updates the light.
    virtual void update(SunAction action);

    /// Passes the color, direction, and shadow map to a shader.
    virtual void uniform(SunAction action);

    /// Sets the resolution of the shadow map.
    void setResolution(glm::ivec2 _resolution) { resolution = _resolution; }

    /// Sets the render target
    void setTarget(SunBase *_target) { target = _target; }
private:
    /// The framebuffer object
    GLuint fbo;

    /// The depth texture
    GLuint texture;

    /// The render target
    SunBase *target;

    /// The resolution of the shadow map
    glm::ivec2 resolution;
};

#endif
