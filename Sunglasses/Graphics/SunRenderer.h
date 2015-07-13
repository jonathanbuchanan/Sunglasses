//
//  Renderer.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/12/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_Renderer_h
#define OpenGL_Test_3_Renderer_h

using namespace std;

#include "SunTextRenderer.h"
#include "SunGUIRenderer.h"
#include "SunDirectionalLightShadowMapRenderer.h"
#include "SunPointLightShadowMapRenderer.h"

#include "SunTexturedQuad.h"

#include "SunScene.h"
#include "SunCamera.h"
#include "SunButtonState.h"

class SunRenderer {
public:
    GLuint HDRframebuffer;
    GLuint colorBuffers[2];
    GLuint depthBuffer;
    
    SunShader final;
    
    GLuint blurFramebuffers[2];
    GLuint blurBuffers[2];
    
    SunShader blur;
    
    GLFWwindow *window;
    
    GLfloat screenWidth;
    GLfloat screenHeight;
    
    SunGUIRenderer GUIRenderer;
    SunDirectionalLightShadowMapRenderer shadowMapRenderer;
    
    SunTexturedQuad quad;
    
    SunScene *scene;
    SunCamera camera;
    
    map<string, SunShader> shaderMap;
    
    vector<SunShaderUniform> HDRUniforms;
    
    SunObject *watch;
    
    SunDirectionalLightObject *dlight;
    SunObject *plane;
    
    void cycle(map<int, SunButtonState> _buttons, GLfloat deltaTime) {
        // Update the scene
        scene->update(_buttons);
        
        // Clear
        clear();
        
        // Render the scene
        glBindFramebuffer(GL_FRAMEBUFFER, HDRframebuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        scene->render(shaderMap, deltaTime);
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        GLboolean horizontal = true;
        GLboolean firstIteration = true;
        GLuint amount = 10;
        
        for (int i = 0; i < amount; i++) {
            glBindFramebuffer(GL_FRAMEBUFFER, blurFramebuffers[horizontal]);
            
            vector<SunShaderUniform> uniforms;
            uniforms.push_back(SunShaderUniform("horizontal", "boolean", &horizontal));
            
            map<string, GLuint> textureMap;
            textureMap["backgroundTexture"] = firstIteration ? colorBuffers[1] : blurBuffers[!horizontal];
            
            quad.render(textureMap, blur, uniforms, false);
            
            horizontal = !horizontal;
            
            if (firstIteration)
                firstIteration = false;
        }
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        clear();
        
        map<string, GLuint> textureMap;
        
        textureMap["backgroundTexture"] = colorBuffers[0];
        textureMap["bloomTexture"] = blurBuffers[!horizontal];
        
        quad.render(textureMap, final, HDRUniforms, true);
        
        // Load the fonts if they aren't loaded
        if (scene->GUIsystem->fontsLoaded == false)
            scene->GUIsystem->loadFonts(&GUIRenderer.textRenderer);
        
        // Render the GUI
        scene->renderGUISystem(&GUIRenderer.textRenderer);
        
        // Swap the buffers
        swapBuffers();
    }
    
    void initialize() {
        setUpGL();
        
        // Set up the GUI renderer
        GUIRenderer = SunGUIRenderer();
        GUIRenderer.initialize();
        
        // Set up the shadow map renderer
        shadowMapRenderer = SunDirectionalLightShadowMapRenderer();
        shadowMapRenderer.initialize();
        
        quad = SunTexturedQuad();
        quad.setUpGL();
        
        scene = new SunScene("SceneDemo.xml", window);
        
        // Set up shader map
        shaderMap["solid"] = SunShader("Graphics/Shaders/BlinnPhongMaterialBoneless.vert", "Graphics/Shaders/BlinnPhongMaterialBoneless.frag");
        shaderMap["textured"] = SunShader("Graphics/Shaders/BlinnPhongTextureBoneless.vert", "Graphics/Shaders/BlinnPhongTextureBoneless.frag");
        
        HDRUniforms.push_back(SunShaderUniform("exposure", "float", new GLfloat(1)));
        HDRUniforms.push_back(SunShaderUniform("doHDR", "boolean", new GLboolean(true)));
        
        final = SunShader("Graphics/Shaders/2DFullscreenQuadVertex.vert", "Graphics/Shaders/2DFullscreenQuadFragment.frag");
        blur = SunShader("Graphics/Shaders/2DFullscreenBlurVertex.vert", "Graphics/Shaders/2DFullscreenBlurFragment.frag");
    }
    
    void setUpGL() {
        glGenFramebuffers(1, &HDRframebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, HDRframebuffer);
        
        glGenTextures(2, colorBuffers);
        
        for (int i = 0; i < 2; i++) {
            glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 1600, 1200, 0, GL_RGB, GL_FLOAT, NULL);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
        }
        
        glBindTexture(GL_TEXTURE_2D, 0);
        
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1600, 1200);
        
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
        
        GLuint colorAttachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
        glDrawBuffers(2, colorAttachments);
        
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        glGenFramebuffers(2, blurFramebuffers);
        glGenTextures(2, blurBuffers);
        
        for (int i = 0; i < 2; i++) {
            glBindFramebuffer(GL_FRAMEBUFFER, blurFramebuffers[i]);
            glBindTexture(GL_TEXTURE_2D, blurBuffers[i]);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 1600, 1200, 0, GL_RGB, GL_FLOAT, NULL);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blurBuffers[i], 0);
        }
    }
    
    void clear() {
        // Clear the scene using this color
        glClearColor(0.0, 0.0, 0.0, 1.0);
        
        // Clear the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void swapBuffers() {
        // Swap the buffers
        glfwSwapBuffers(window);
    }
    
    SunRenderer() {
        
    }
    
private:
    
};

#endif
