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
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class SunPointLightObject : public SunObject {
public:
    // Color
    glm::vec3 color;
    
    // Position
    glm::vec3 position;
    
    // Attenuation
    // Constant, linear, and quadratic terms
    GLfloat constantTerm;
    GLfloat linearTerm;
    GLfloat quadraticTerm;
    
    SunPointLightObject() {
        
    }
    
    SunPointLightObject(glm::vec3 _color, glm::vec3 _position) {
        color = _color;
        position = _position;
    }
    
    SunPointLightObject(string _name) {
        name = _name;
        
        initializeDefaultPropertyAndFunctionMap();
    }
    
    void passPerFrameUniforms(SunNodeSentAction _action) {
        SunObject::passPerFrameUniforms(_action);
        
        SunShader _shader = *(SunShader *)_action.parameters["shader"];
        
        // Set the uniforms for the point light's diffuse and specular colors
        glUniform3f(glGetUniformLocation(_shader.program, "pointLight.color"), color.r, color.g, color.b);
        
        // Set the uniform for the point light's position
        glUniform3f(glGetUniformLocation(_shader.program, "pointLight.position"), position.x, position.y, position.z);
        
        // Set the uniforms for the point light's constant, linear, and quadratic terms
        glUniform1f(glGetUniformLocation(_shader.program, "pointLight.constant"), constantTerm);
        glUniform1f(glGetUniformLocation(_shader.program, "pointLight.linear"), linearTerm);
        glUniform1f(glGetUniformLocation(_shader.program, "pointLight.quadratic"), quadraticTerm);
    }
private:
    
};

#endif
