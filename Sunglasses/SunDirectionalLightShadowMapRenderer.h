//
//  ShadowMapRenderer.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/29/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_ShadowMapRenderer_h
#define OpenGL_Test_3_ShadowMapRenderer_h

using namespace std;

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "SunShader.h"

#include "SunScene.h"
#include "SunObject.h"
#include "SunDirectionalLightObject.h"

class SunDirectionalLightShadowMapRenderer {
public:
    SunShader shader;
    GLuint FBO;
    GLuint depthMap;
    
    SunDirectionalLightShadowMapRenderer() {
        
    }
    
    void initialize() {
        shader = SunShader("ShadowMapVertex.vert", "ShadowMapFragment.frag");
        
        glGenFramebuffers(1, &FBO);
        
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 8192, 8192, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        GLfloat borderColor[] = {1.0, 1.0, 1.0, 1.0};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    void renderDirectionalLight(SunDirectionalLightObject *_directionalLight, GLfloat _deltaTime, glm::vec3 _target, SunScene *_scene) {
        glCullFace(GL_FRONT);
        
        shader.use();
        
        passLightSpaceMatrix(shader, _directionalLight, _target);
        
        glViewport(0, 0, 8192, 8192);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        
        _scene->render(shader, _deltaTime);
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        glCullFace(GL_BACK);
    }
    
    void passLightSpaceMatrix(SunShader _shader, SunDirectionalLightObject *_directionalLight, glm::vec3 _target) {
        glm::mat4 projectionMatrix = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.001f, 30.0f);
        glm::mat4 viewMatrix = glm::lookAt(-_directionalLight->direction, _target, glm::vec3(1.0f));
        
        glm::mat4 lightMatrix = projectionMatrix * viewMatrix;
        
        glUniformMatrix4fv(glGetUniformLocation(_shader.program, "lightMatrix"), 1, GL_FALSE, glm::value_ptr(lightMatrix));
    }
    
private:
    
};

#endif
