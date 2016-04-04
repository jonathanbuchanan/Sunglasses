// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNDIRECTIONALLIGHT_H
#define SUNDIRECTIONALLIGHT_H

#include "../Core/SunNode.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
private:
    /// The color of the directional light
    glm::vec3 color;

    /// The direction of the directional light
    glm::vec3 direction;
/*public:
    SunDirectionalLight();
    SunDirectionalLight(glm::vec3 _color, glm::vec3 _direction);
    SunDirectionalLight(string _name);

    virtual void init();
    virtual void uniform(SunAction action);
    void shadowMap(SunAction action);
    void initializeShadowMap();

    inline glm::vec3 & getColor() { return color; }
    inline void setColor(glm::vec3 _color) { color = _color; }

    inline glm::vec3 & getDirection() { return direction; }
    inline void setDirection(glm::vec3 _direction) { direction = _direction; }

	inline void setCountUniform(std::string c) { countUniform = c; }
	inline void setArrayUniform(std::string a) { arrayUniform = a; }

	inline GLboolean & getShadows() { return shadows; }
	inline void setShadows(GLboolean _s) { shadows = _s; }

	inline glm::vec2 & getShadowMapSize() { return shadowMapSize; }
	inline void setShadowMapSize(glm::vec2 _s) { shadowMapSize = _s; }
private:
    // Diffuse and specular
    glm::vec3 color;

    // Direction
    glm::vec3 direction;

	// Shaders
	int id;
	std::string countUniform;
	std::string arrayUniform;

	static int lastId;

    // Shadow Mapping
    GLboolean shadows;
    glm::vec2 shadowMapSize = glm::vec2(1024.0f, 1024.0f);
    GLuint shadowMapFramebuffer;
    GLuint shadowMapTexture;*/
};

#endif
