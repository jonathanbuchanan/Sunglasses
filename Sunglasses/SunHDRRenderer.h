//
//  SunHDRRenderer.h
//  Sunglasses
//
//  Created by Jonathan Buchanan on 7/7/15.
//
//

#ifndef Sunglasses_SunHDRRenderer_h
#define Sunglasses_SunHDRRenderer_h

#include "SunScene.h"
#include <map>

class SunHDRRenderer {
public:
    GLuint HDRframebuffer;
    GLuint colorBuffer;
    GLuint depthBuffer;
    
    SunHDRRenderer() {
        
    }
    
    void initialize() {
        glGenFramebuffers(1, &HDRframebuffer);
        
        glGenTextures(1, &colorBuffer);
        glBindTexture(GL_TEXTURE_2D, colorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 1600, 1200, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1600, 1200);
        
        glBindFramebuffer(GL_FRAMEBUFFER, HDRframebuffer);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    void renderScene(SunScene *_scene, GLfloat _deltaTime,  map<string, SunShader> _shaderMap) {
        glBindFramebuffer(GL_FRAMEBUFFER, HDRframebuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        _scene->render(_shaderMap, _deltaTime);
    }
    
private:
    
};

#endif
