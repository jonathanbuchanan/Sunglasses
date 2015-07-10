//
//  SunPointLightShadowMapRenderer.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/31/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_SunPointLightShadowMapRenderer_h
#define OpenGL_Test_3_SunPointLightShadowMapRenderer_h

using namespace std;

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "SunShader.h"

#include "SunScene.h"
#include "SunObject.h"
#include "SunPointLightObject.h"

class SunPointLightShadowMapRenderer {
public:
    SunShader shader;
    GLuint FBO;
    GLuint depthCubemap;
    
    SunPointLightShadowMapRenderer() {
        
    }
    
    void initialize() {
        shader = SunShader("PointShadowMapVertex.vert", "PointShadowMapGeometry.geom", "PointShadowMapFragment.frag");
        
        glGenFramebuffers(1, &FBO);
        
        glGenTextures(1, &depthCubemap);
        
        glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
        for (int i = 0; i < 6; ++i) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, 2048, 2048, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        }
        
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    void renderPointLight(SunPointLightObject *_pointLight, GLfloat _deltaTime, SunScene *_scene) {
        glViewport(0, 0, 2048, 2048);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        
        shader.use();
        
        passLightSpaceMatrix(shader, _pointLight);
        
        map<string, SunShader> shaderMap;
        shaderMap["all"] = shader;
        
        _scene->render(shaderMap, _deltaTime);
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    void passLightSpaceMatrix(SunShader _shader, SunPointLightObject *_pointLight) {
        glm::mat4 projectionMatrix = glm::perspective(90.0f, 1.0f, 0.01f, 10.0f);
        
        vector<glm::mat4> lightMatrices;
        lightMatrices.push_back(projectionMatrix * glm::lookAt(_pointLight->position, _pointLight->position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
        lightMatrices.push_back(projectionMatrix * glm::lookAt(_pointLight->position, _pointLight->position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
        lightMatrices.push_back(projectionMatrix * glm::lookAt(_pointLight->position, _pointLight->position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
        lightMatrices.push_back(projectionMatrix * glm::lookAt(_pointLight->position, _pointLight->position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
        lightMatrices.push_back(projectionMatrix * glm::lookAt(_pointLight->position, _pointLight->position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
        lightMatrices.push_back(projectionMatrix * glm::lookAt(_pointLight->position, _pointLight->position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));
        
        for (int i = 0; i < 6; ++i)
            glUniformMatrix4fv(glGetUniformLocation(_shader.program, ("lightMatrices[" + std::to_string(i) + "]").c_str()), 1, GL_FALSE, glm::value_ptr(lightMatrices[i]));
        glUniform1f(glGetUniformLocation(_shader.program, "farPlane"), 10.0f);
        glUniform3fv(glGetUniformLocation(_shader.program, "lightPosition"), 1, &_pointLight->position[0]);
    }
private:
    
};

#endif
