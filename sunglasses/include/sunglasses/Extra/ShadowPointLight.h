// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SHADOWPOINTLIGHT_H
#define SHADOWPOINTLIGHT_H

#include "PointLight.h"

namespace sunglasses {

/// A point light that renders shadow maps
class ShadowPointLight : public PointLight {
public:
    /// A constructor
    ShadowPointLight();

    /// A constructor
    /**
     * @param _color The color of the point light
     * @param _position The position of the point light
     */
    ShadowPointLight(glm::vec3 _color, glm::vec3 _position);

    /// Initializes the point light
    virtual void init();

    /// Renders the shadow map
    virtual void shadowMap(Action action);

    /// Updates the point light
    virtual void update(Action action);

    /// Passes the color, position, and shadow map to a shader.
    virtual void uniform(Action action);

    /// Sets the render target for shadow maps
    void setTarget(Base *_target) { target = _target; }

    /// Sets the resolution of the shadow map
    void setResolution(GLint _resolution) { resolution = _resolution; }

    /// Sets the near plane
    void setNearPlane(GLfloat _nearPlane) { nearPlane = _nearPlane; }

    /// Sets the far plane
    void setFarPlane(GLfloat _farPlane) { farPlane = _farPlane; }
private:
    /// The framebuffer object
    GLuint fbo;

    /// The depth cubemap
    GLuint texture;

    /// The render target
    Base *target;

    /// The resolution of the shadow map (length of the cubemap edges)
    GLint resolution;

    /// The near plane of the shadow map projection matrix
    GLfloat nearPlane = 0.01f;

    /// The far plane of the shadow map projection matrix
    GLfloat farPlane = 100.0f;
};

} // namespace

#endif
