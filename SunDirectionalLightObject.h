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
private:
    // Diffuse and specular
    glm::vec3 color;

    // Direction
    glm::vec3 direction;
};

#endif
