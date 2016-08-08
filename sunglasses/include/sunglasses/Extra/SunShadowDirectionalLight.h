// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNSHADOWDIRECTIONALLIGHT_H
#define SUNSHADOWDIRECTIONALLIGHT_H

#include "SunDirectionalLight.h"

namespace sunglasses {

/// A directional light that renders shadow maps
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

    /// Sets the near plane
    void setNearPlane(GLfloat _nearPlane) { nearPlane = _nearPlane; }

    /// Sets the far plane
    void setFarPlane(GLfloat _farPlane) { farPlane = _farPlane; }

    /// Sets the size of the shadow map
    void setSize(glm::vec2 _size) { size = _size; }

    /// Sets the target of the shadow map
    void setCenter(glm::vec3 _center) { center = _center; }

    /// Sets the distance of the shadow map
    void setDistance(GLfloat _distance) { distance = _distance; }
private:
    /// The framebuffer object
    GLuint fbo;

    /// The depth texture
    GLuint texture;

    /// The render target
    SunBase *target;

    /// The resolution of the shadow map
    glm::ivec2 resolution;

    /// The near plane of the shadow map projection matrix
    GLfloat nearPlane = 0.01f;

    /// The far plane of the shadow map projection matrix
    GLfloat farPlane = 100.0f;

    /// The size of the shadow map
    glm::vec2 size = glm::vec2(10.0f, 10.0f);

    /// The center of the shadow map
    /**
     * This vector is the center of the shadow map. When the shadow map is rendered
     * this position is at the center of the shadow map.
     */
    glm::vec3 center = glm::vec3(0.0f);

    /// The distance of the 'camera' to the center
    /**
     * This value represents the distance of the 'camera' of the shadow map
     * to the center of the shadow map. Because directional shadow maps
     * are rendered using an orthographic projection matrix, it doesn't
     * change the appearance of the shadows or the area mapped, but it may
     * prevent some clipping from occuring. Keep the far plane value in mind
     * while setting this.
     */
    GLfloat distance = 10.0f;
};

} // namespace

#endif
