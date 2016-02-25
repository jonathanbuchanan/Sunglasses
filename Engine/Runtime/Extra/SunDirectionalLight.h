// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef OpenGL_Test_3_SunDirectionalLightObject_h
#define OpenGL_Test_3_SunDirectionalLightObject_h

#include "./SunObject.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SunDirectionalLight : public SunObject {
public:
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
    GLuint shadowMapTexture;
};

#endif
