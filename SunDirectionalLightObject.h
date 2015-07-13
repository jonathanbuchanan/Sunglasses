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
    // Diffuse and specular
    glm::vec3 color;
    
    // Direction
    glm::vec3 direction;
    
    SunDirectionalLightObject() {
        
    }
    
    SunDirectionalLightObject(glm::vec3 _color, glm::vec3 _direction) {
        color = _color;
        direction = _direction;
    }
    
    SunDirectionalLightObject(string _name) {
        name = _name;
        
        initializeDefaultPropertyAndFunctionMap();
    }
    
    void passPerFrameUniforms(SunNodeSentAction _action) {
        SunObject::passPerFrameUniforms(_action);
        
        SunShader _shader = *(SunShader *)_action.parameters["shader"];
        
        // Set the uniforms for the directional light's diffuse and specular colors
        glUniform3f(glGetUniformLocation(_shader.program, "directionalLight.color"), color.r, color.g, color.b);
        
        // Set the unifrom for the directional light's direction
        glUniform3f(glGetUniformLocation(_shader.program, "directionalLight.direction"), direction.x, direction.y, direction.z);
    }
private:
    
};

#endif
