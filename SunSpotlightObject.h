//
//  SunSpotlightObject.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/24/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_SunSpotlightObject_h
#define OpenGL_Test_3_SunSpotlightObject_h

#include "./SunObject.h"

#include <GL/glew.h>
#include "./Libraries/glm/glm.hpp"
#include "./Libraries/glm/gtc/matrix_transform.hpp"

struct SunSpotlight {
    // Diffuse, specular, and cutoff
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
    GLfloat cutoff;
    
    // Position and direction
    glm::vec3 position;
    glm::vec3 direction;
    
    // Attenuation
    // Constant, linear, and quadratic terms
    GLfloat constantTerm;
    GLfloat linearTerm;
    GLfloat quadraticTerm;
};

class SunSpotlightObject : public SunObject {
    SunSpotlight spotlight;
    
    SunSpotlightObject() {
        
    }
    
    SunSpotlightObject(SunSpotlight _spotlight) {
        spotlight = _spotlight;
    }
    
    void passPerFrameUniforms(SunNodeSentAction _action) {
        SunObject::passPerFrameUniforms(_action);
        
        SunShader _shader = *(SunShader *)_action.parameters["shader"];
        
        // Set the uniforms for the spotlight's diffuse and specular colors and cutoff value
        glUniform3f(_shader.getUniformLocation("spotlight.diffuseColor"), spotlight.diffuseColor.x, spotlight.diffuseColor.y, spotlight.diffuseColor.z);
        glUniform3f(_shader.getUniformLocation("spotlight.specularColor"), spotlight.specularColor.x, spotlight.specularColor.y, spotlight.specularColor.z);
        glUniform1f(_shader.getUniformLocation("spotlight.cutoff"), spotlight.cutoff);
        
        // Set the uniform for the spotlight's position and direction
        glUniform3f(_shader.getUniformLocation("spotlight.position"), spotlight.position.x, spotlight.position.y, spotlight.position.z);
        glUniform3f(_shader.getUniformLocation("spotlight.direction"), spotlight.direction.x, spotlight.direction.y, spotlight.direction.z);

        // Set the uniforms for the spotlight's constant, linear, and quadratic terms
        glUniform1f(_shader.getUniformLocation("spotlight.constant"), spotlight.constantTerm);
        glUniform1f(_shader.getUniformLocation("spotlight.linear"), spotlight.linearTerm);
        glUniform1f(_shader.getUniformLocation("spotlight.quadratic"), spotlight.quadraticTerm);
    }
};

#endif
