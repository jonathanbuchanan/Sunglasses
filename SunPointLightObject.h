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

#include <GL/glew.h>
#include "./Libraries/glm/glm.hpp"
#include "./Libraries/glm/gtc/matrix_transform.hpp"

class SunPointLightObject : public SunObject {
public:
    SunPointLightObject();
    SunPointLightObject(glm::vec3 _color, glm::vec3 _position);
    SunPointLightObject(string _name);
    
    virtual void initializeDefaultPropertyAndFunctionMap();
    void passPerFrameUniforms(SunNodeSentAction _action);
    
    inline glm::vec3 & getColor() { return color; }
    inline void setColor(glm::vec3 _color) { color = _color; }
    inline void setColorR(GLfloat r) { color.r = r; }
    inline void setColorG(GLfloat g) { color.g = g; }
    inline void setColorB(GLfloat b) { color.b = b; }
    
    inline GLboolean & getAttenuate() { return attenuate; }
    inline void setAttenuate(GLboolean _attenuate) { attenuate = _attenuate; }
    
    inline int & getPointLightID() { return pointLightID; }
    inline void setPointLightID(int _p) { pointLightID = _p; }
private:
    // Color
    glm::vec3 color;
    
    // Attenuation
    GLboolean attenuate;
    
    // Point Light ID
    int pointLightID;
};

#endif
