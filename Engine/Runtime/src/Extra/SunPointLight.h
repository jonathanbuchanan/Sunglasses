// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef OpenGL_Test_3_SunPointLightObject_h
#define OpenGL_Test_3_SunPointLightObject_h

#include "../Core/SunObject.h"
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Core/SunGame.h" 

class SunPointLight : public SunObject {
public:
    SunPointLight();
    SunPointLight(glm::vec3 _color, glm::vec3 _position);
    SunPointLight(string _name);

    virtual void init();
    void uniform(SunAction action);
    void passPOVUniforms(SunShader _shader);
	void shadowMap(SunAction action);
	void initializeShadowMap();

    inline glm::vec3 & getColor() { return color; }
    inline void setColor(glm::vec3 _color) { color = _color; }

    inline GLboolean & getAttenuate() { return attenuate; }
    inline void setAttenuate(GLboolean _attenuate) { attenuate = _attenuate; }

	inline void setCountUniform(std::string c) { countUniform = c; }
	inline void setArrayUniform(std::string a) { arrayUniform = a; }

	inline GLboolean & getShadows() { return shadows; }
	inline void setShadows(GLboolean _s) { shadows = _s; }

	inline glm::vec2 & getShadowMapSize() { return shadowMapSize; }
	inline void setShadowMapSize(glm::vec2 _s) { shadowMapSize = _s; }
private:
    // Color
    glm::vec3 color;

    // Attenuation
    GLboolean attenuate;

	// Shaders
	int id;
	std::string countUniform;
	std::string arrayUniform;

	static int lastId;

	// Shadow Maps
	GLboolean shadows = false;
	glm::vec2 shadowMapSize = glm::vec2(1024.0f, 1024.0f);
	GLuint shadowMapFramebuffer;
	GLuint shadowMapTexture;
	vector<glm::mat4> lightTransforms;
	//vector<SunShaderUniformObject> _lightTransforms;
};

#endif
