//
//  SunPointLightObject.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/24/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_SunPointLightObject_h
#define OpenGL_Test_3_SunPointLightObject_h

#include "SunObject.h"
#include <vector>
using namespace std;

#include <GL/glew.h>
#include "./Libraries/glm/glm.hpp"
#include "./Libraries/glm/gtc/matrix_transform.hpp"
#include "./SunGame.h"
#include "./Graphics/Shaders/SunShaderUniformObject.h"

class SunPointLightObject : public SunObject {
public:
    SunPointLightObject();
    SunPointLightObject(glm::vec3 _color, glm::vec3 _position);
    SunPointLightObject(string _name);
    
    virtual void initializeDefaultPropertyAndFunctionMap();
    void passPerFrameUniforms(SunNodeSentAction _action);
    void passPOVUniforms(SunShader _shader);
	void shadowMap(SunNodeSentAction _action);
	void initializeShadowMap();
    
    inline glm::vec3 & getColor() { return color; }
    inline void setColor(glm::vec3 _color) { color = _color; }
    inline void setColorR(GLfloat r) { color.r = r; }
    inline void setColorG(GLfloat g) { color.g = g; }
    inline void setColorB(GLfloat b) { color.b = b; }
    
    inline GLboolean & getAttenuate() { return attenuate; }
    inline void setAttenuate(GLboolean _attenuate) { attenuate = _attenuate; }
    
    inline int & getPointLightID() { return pointLightID; }
    inline void setPointLightID(int _p) { pointLightID = _p; }
	
	inline GLboolean & getShadows() { return shadows; }
	inline void setShadows(GLboolean _s) { shadows = _s; }
	
	inline glm::vec2 & getShadowMapSize() { return shadowMapSize; }
	inline void setShadowMapSize(glm::vec2 _s) { shadowMapSize = _s; }
private:
    // Color
    glm::vec3 color;
    
    // Attenuation
    GLboolean attenuate;
    
    // Point Light ID
    int pointLightID;
	
	// Shadow Maps
	GLboolean shadows;
	glm::vec2 shadowMapSize = glm::vec2(1024.0f, 1024.0f);
	GLuint shadowMapFramebuffer;
	GLuint shadowMapTexture;
	vector<glm::mat4> lightTransforms;
	vector<SunShaderUniformObject> _lightTransforms;
};

#endif
