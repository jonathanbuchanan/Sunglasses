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

#include "./SunTextRenderer.h"
#include "./GUI/SunGUIRenderer.h"
#include "./SunDirectionalLightShadowMapRenderer.h"
#include "./SunPointLightShadowMapRenderer.h"

#include "./SunTexturedQuad.h"
#include "../SunNode.h"
#include "./SunCamera.h"
#include "../SunButtonState.h"

enum SunRenderingMode {
    SunRenderingModeForward,
    SunRenderingModeDeferredShading
};

typedef GLuint SunFramebufferObject;
typedef GLuint SunFramebufferTextureObject;
typedef GLuint SunFramebufferColorAttachmentObject;

struct SunFramebuffer {
    GLuint framebuffer;
    GLuint renderbuffer;
    vector<SunFramebufferColorAttachmentObject> colorAttachments;
    map<string, SunFramebufferTextureObject> textures;
};

typedef map<string, SunFramebufferTextureObject>::iterator SunFramebufferTextureObjectIterator;

class SunRenderer {
public:
    // Rendering Objects
    SunRenderingMode renderMode;
    
    map<string, SunFramebuffer> framebuffers;
    
    map<string, SunShader> shaderMap;
    
    vector<SunShaderUniform> HDRUniforms;
    
    SunTexturedQuad quad;
    
    // Window and window size
    
    GLFWwindow *window;
    
    GLfloat screenWidth;
    GLfloat screenHeight;
    
    // Scene Objects
    SunNode *scene;
    
    SunRenderer() {
        
    }
    
    SunRenderer(SunRenderingMode _renderMode) {
        renderMode = _renderMode;
        
        //initialize();
    }
    
    void cycle(map<int, SunButtonState> _buttons, GLfloat deltaTime) {
        render(deltaTime);
    }
    
    void render(GLfloat _deltaTime) {
        if (renderMode == SunRenderingModeForward) {
            // Clear
            clear();
        
            // Render the scene
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffers["HDR"].framebuffer);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            SunNodeSentAction renderAction;
            renderAction.action = "render";
            renderAction.parameters["renderType"] = new int(SunMeshRenderTypeSolid);
            renderAction.parameters["shaderMap"] = &shaderMap;
            renderAction.parameters["deltaTime"] = &_deltaTime;
            
            sendAction(renderAction, scene);
            
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            clear();
            
            GLboolean horizontal = true;
            GLboolean firstIteration = true;
            GLuint amount = 10;
            
            for (int i = 0; i < amount; i++) {
                SunFramebuffer currentFramebuffer;
                SunFramebuffer otherFramebuffer;
                
                if (horizontal == false) {
                    currentFramebuffer = framebuffers["blur1"];
                    otherFramebuffer = framebuffers["blur2"];
                } else if (horizontal == true) {
                    currentFramebuffer = framebuffers["blur2"];
                    otherFramebuffer = framebuffers["blur1"];
                }
                
                glBindFramebuffer(GL_FRAMEBUFFER, currentFramebuffer.framebuffer);
                
                vector<SunShaderUniform> uniforms;
                uniforms.push_back(SunShaderUniform("horizontal", "boolean", &horizontal));
                
                map<string, GLuint> textureMap;
                textureMap["backgroundTexture"] = firstIteration ? framebuffers["HDR"].textures["bloom"] : otherFramebuffer.textures["color"];
                
                quad.render(textureMap, shaderMap["blur"], uniforms, false);
                
                horizontal = !horizontal;
                
                if (firstIteration)
                    firstIteration = false;
            }
            
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            clear();
            
            map<string, GLuint> textureMap;
            
            textureMap["backgroundTexture"] = framebuffers["HDR"].textures["HDR"];
            textureMap["bloomTexture"] = framebuffers["blur1"].textures["color"];
            
            quad.render(textureMap, shaderMap["final"], HDRUniforms, true);
            
            // Render the GUI
            SunNodeSentAction action;
            action.action = "renderGUISystem";
            
            sendAction(action, scene);
            
            // Swap the buffers
            swapBuffers();
        } else if (renderMode == SunRenderingModeDeferredShading) {
            // Clear
            clear();
        }
    }
    
    void initialize() {
        setUpGL();
    }
    
    void setUpGL() {
        if (renderMode == SunRenderingModeForward) {
            SunFramebuffer HDR;
            
            glGenFramebuffers(1, &HDR.framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, HDR.framebuffer);
            
            glGenTextures(1, &HDR.textures["HDR"]);
            glGenTextures(1, &HDR.textures["bloom"]);
            
            int i = 0;
            for (SunFramebufferTextureObjectIterator iterator = HDR.textures.begin(); iterator != HDR.textures.end(); iterator++) {
                glBindTexture(GL_TEXTURE_2D, iterator->second);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 1600, 1200, 0, GL_RGB, GL_FLOAT, NULL);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, iterator->second, 0);
                i++;
            }

            glBindTexture(GL_TEXTURE_2D, 0);
            
            glGenRenderbuffers(1, &HDR.renderbuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, HDR.renderbuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1600, 1200);

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, HDR.renderbuffer);
            
            GLuint colorAttachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
            glDrawBuffers(2, colorAttachments);
            
            framebuffers["HDR"] = HDR;

            
            
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "Frame buffer not complete!" << std::endl;
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            
            SunFramebuffer blur1;
            
            glGenFramebuffers(1, &blur1.framebuffer);
            glGenTextures(1, &blur1.textures["color"]);
            
            glBindFramebuffer(GL_FRAMEBUFFER, blur1.framebuffer);
            glBindTexture(GL_TEXTURE_2D, blur1.textures["color"]);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 1600, 1200, 0, GL_RGB, GL_FLOAT, NULL);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blur1.textures["color"], 0);
            
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "Framebuffer not complete!" << std::endl;
            
            framebuffers["blur1"] = blur1;
            
            SunFramebuffer blur2;
            
            glGenFramebuffers(1, &blur2.framebuffer);
            glGenTextures(1, &blur2.textures["color"]);
            
            glBindFramebuffer(GL_FRAMEBUFFER, blur2.framebuffer);
            glBindTexture(GL_TEXTURE_2D, blur2.textures["color"]);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 1600, 1200, 0, GL_RGB, GL_FLOAT, NULL);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blur2.textures["color"], 0);
            
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "Framebuffer not complete!" << std::endl;
            
            framebuffers["blur2"] = blur2;

            quad = SunTexturedQuad();
            quad.setUpGL();

            // Set up shader map
            shaderMap["solid"] = SunShader("./Graphics/Shaders/BlinnPhongMaterialBoneless.vert", "./Graphics/Shaders/BlinnPhongMaterialBoneless.frag");
            shaderMap["textured"] = SunShader("./Graphics/Shaders/BlinnPhongTextureBoneless.vert", "./Graphics/Shaders/BlinnPhongTextureBoneless.frag");
            
            HDRUniforms.push_back(SunShaderUniform("exposure", "float", new GLfloat(1)));
            HDRUniforms.push_back(SunShaderUniform("doHDR", "boolean", new GLboolean(true)));

            shaderMap["final"] = SunShader("./Graphics/Shaders/2DFullscreenQuadVertex.vert", "./Graphics/Shaders/2DFullscreenQuadFragment.frag");
            shaderMap["final"].uniforms["exposure"] = SunShaderUniform("exposure", "float", new GLfloat(1));
            shaderMap["final"].uniforms["doHDR"] = SunShaderUniform("doHDR", "boolean", new GLboolean(true));
            
            shaderMap["blur"] = SunShader("./Graphics/Shaders/2DFullscreenBlurVertex.vert", "./Graphics/Shaders/2DFullscreenBlurFragment.frag");
        } else if (renderMode == SunRenderingModeDeferredShading) {
            
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
    
private:
    
};

#endif