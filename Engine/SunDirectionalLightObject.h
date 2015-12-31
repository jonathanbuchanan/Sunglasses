//
//  SunDirectionalLightObject.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/24/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_SunDirectionalLightObject_h
#define OpenGL_Test_3_SunDirectionalLightObject_h

#include "./SunObject.h"

#include <GL/glew.h>
#include "./Libraries/glm/glm.hpp"
#include "./Libraries/glm/gtc/matrix_transform.hpp"

class SunDirectionalLightObject : public SunObject {
public:
    SunDirectionalLightObject();
    SunDirectionalLightObject(glm::vec3 _color, glm::vec3 _direction);
    SunDirectionalLightObject(string _name);
    
    virtual void initializeDefaultPropertyAndFunctionMap();
    virtual void passPerFrameUniforms(SunNodeSentAction _action);
    void shadowMap(SunNodeSentAction _action);
    void initializeShadowMap();
    
    inline glm::vec3 & getColor() { return color; }
    inline void setColor(glm::vec3 _color) { color = _color; }
    inline void setColorR(GLfloat r) { color.r = r; }
    inline void setColorG(GLfloat g) { color.g = g; }
    inline void setColorB(GLfloat b) { color.b = b; }
    
    inline glm::vec3 & getDirection() { return direction; }
    inline void setDirection(glm::vec3 _direction) { direction = _direction; }
    inline void setDirectionX(GLfloat x) { direction.x = x; }
    inline void setDirectionY(GLfloat y) { direction.y = y; }
    inline void setDirectionZ(GLfloat z) { direction.z = z; }
    
    inline int & getDirectionalLightID() { return directionalLightID; }
    inline void setDirectionalLightID(int _i) { directionalLightID = _i; }
    
    inline GLboolean & getShadows() { return shadows; }
	inline void setShadows(GLboolean _s) { shadows = _s; }
	
	inline glm::vec2 & getShadowMapSize() { return shadowMapSize; }
	inline void setShadowMapSize(glm::vec2 _s) { shadowMapSize = _s; }
private:
    // Diffuse and specular
    glm::vec3 color;

    // Direction
    glm::vec3 direction;
    
    // Directional Light ID
    int directionalLightID;
    
    // Shadow Mapping
    GLboolean shadows;
    glm::vec2 shadowMapSize = glm::vec2(1024.0f, 1024.0f);
    GLuint shadowMapFramebuffer;
    GLuint shadowMapTexture;
};

#endif
