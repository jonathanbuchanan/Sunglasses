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

#include <iostream>

#include "./SunTextRenderer.h"
#include "./GUI/SunGUIRenderer.h"
#include "./SunDirectionalLightShadowMapRenderer.h"
#include "./SunPointLightShadowMapRenderer.h"
#include "./SunRenderingNode.h"

#include "./SunTexturedQuad.h"
#include "../SunNode.h"
#include "./SunPrimitives.h"
#include "./SunCamera.h"
#include "../SunButtonState.h"

enum SunRenderingMode {
    SunRenderingModeForward,
    SunRenderingModeDeferredShading
};

class SunRenderer {
public:
    // Rendering Objects
    SunRenderingMode renderMode;
    
    map<string, SunFramebuffer> framebuffers;
    
    map<string, SunShader> shaderMap;
    
    SunTexturedQuad quad;
    
    // Window and window size
    
    GLFWwindow *window;
    
    GLfloat screenWidth;
    GLfloat screenHeight;
    
    // Scene Objects
    SunNode *scene;
    SunRenderingNode *rootRenderNode;
    
    SunRenderer() {
        
    }
    
    SunRenderer(SunRenderingMode _renderMode) {
        renderMode = _renderMode;
    }
    
    void cycle(map<int, SunButtonState> _buttons, GLfloat deltaTime) {
        render(deltaTime);
    }
    
    void render(GLfloat _deltaTime) {
        SunNodeSentAction renderAction;
        renderAction.action = "render";
        renderAction.parameters["deltaTime"] = &_deltaTime;
        renderAction.recursive = true;
        
        sendAction(renderAction, rootRenderNode);
        
        // Render the GUI
        SunNodeSentAction action;
        action.action = "renderGUISystem";

        sendAction(action, scene);

        // Swap the buffers
        swapBuffers();
        /*if (renderMode == SunRenderingModeForward) {
            // Clear
            clear();
        
            // Render the scene
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffers["HDR"].framebuffer);
            clear();
            
            SunNodeSentAction renderAction;
            renderAction.action = "render";
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
                
                quad.render(textureMap, shaderMap["blur"], uniforms);
                
                horizontal = !horizontal;
                
                if (firstIteration)
                    firstIteration = false;
            }
            
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            clear();
            
            map<string, GLuint> textureMap;
            
            textureMap["t.backgroundTexture"] = framebuffers["HDR"].textures["HDR"];
            textureMap["t.bloomTexture"] = framebuffers["blur1"].textures["color"];
            
            quad.render(textureMap, shaderMap["final"]);
            
            // Render the GUI
            SunNodeSentAction action;
            action.action = "renderGUISystem";
            
            sendAction(action, scene);
            
            // Swap the buffers
            swapBuffers();
        } else if (renderMode == SunRenderingModeDeferredShading) {
            // Clear
            clear();
        
            // Render the scene
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffers["GBuffer"].framebuffer);
            clear();
            
            SunNodeSentAction renderAction;
            renderAction.action = "render";
            renderAction.parameters["shaderMap"] = &shaderMap;
            renderAction.parameters["deltaTime"] = &_deltaTime;
            
            sendAction(renderAction, scene);
            
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            clear();
            
            map<string, GLuint> textureMap;
            
            textureMap["g_position"] = framebuffers["GBuffer"].textures["position"];
            textureMap["g_normal"] = framebuffers["GBuffer"].textures["normal"];
            textureMap["g_color"] = framebuffers["GBuffer"].textures["color"];
            
            shaderMap["final"].use();
            
            SunNodeSentAction uniformAction;
            uniformAction.action = "passPerFrameUniforms";
            uniformAction.parameters["shader"] = &shaderMap["final"];
            
            SunNodeSentActionCondition condition;
            condition.nodeProperty = "type";
            condition.comparativeProperty = SunNodeProperty(new string("light"), SunNodePropertyTypeString);
            condition.conditionType = SunNodeSentActionConditionTypeEqualTo;
            
            vector<SunNodeSentActionCondition> conditions;
            conditions.push_back(condition);
            
            uniformAction.parameters["conditions"] = &conditions;
            
            sendAction(uniformAction, scene);
            
            quad.renderWithUsedShader(textureMap, shaderMap["final"]);
            
            // Render the GUI
            SunNodeSentAction action;
            action.action = "renderGUISystem";
            
            sendAction(action, scene);
            
            // Swap the buffers
            swapBuffers();
        }*/
        
    }
    
    void passSceneUniforms(SunShader *_shader) {
        SunNodeSentAction uniformAction;
        uniformAction.action = "passPerFrameUniforms";
        uniformAction.parameters["shader"] = _shader;
        
        sendAction(uniformAction, scene);
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

            shaderMap["final"] = SunShader("./Graphics/Shaders/2DFullscreenQuadVertex.vert", "./Graphics/Shaders/2DFullscreenQuadFragment.frag");
            shaderMap["final"].uniforms["exposure"] = SunShaderUniform("exposure", "float", new GLfloat(1));
            shaderMap["final"].uniforms["doHDR"] = SunShaderUniform("doHDR", "boolean", new GLboolean(true));
            
            shaderMap["blur"] = SunShader("./Graphics/Shaders/2DFullscreenBlurVertex.vert", "./Graphics/Shaders/2DFullscreenBlurFragment.frag");
        } else if (renderMode == SunRenderingModeDeferredShading) {
            SunFramebuffer GBuffer;
            
            glGenFramebuffers(1, &GBuffer.framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, GBuffer.framebuffer);
            
            glGenTextures(1, &GBuffer.textures["position"]);
            glBindTexture(GL_TEXTURE_2D, GBuffer.textures["position"]);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 1600, 1200, 0, GL_RGB, GL_FLOAT, NULL);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, GBuffer.textures["position"], 0);
            
            
            glGenTextures(1, &GBuffer.textures["normal"]);
            glBindTexture(GL_TEXTURE_2D, GBuffer.textures["normal"]);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 1600, 1200, 0, GL_RGB, GL_FLOAT, NULL);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, GBuffer.textures["normal"], 0);
            
            
            glGenTextures(1, &GBuffer.textures["color"]);
            glBindTexture(GL_TEXTURE_2D, GBuffer.textures["color"]);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1600, 1200, 0, GL_RGBA, GL_FLOAT, NULL);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, GBuffer.textures["color"], 0);
            
            glBindTexture(GL_TEXTURE_2D, 0);

            glGenRenderbuffers(1, &GBuffer.renderbuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, GBuffer.renderbuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1600, 1200);

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, GBuffer.renderbuffer);

            GLuint colorAttachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
            glDrawBuffers(3, colorAttachments);
            
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "Framebuffer not complete!" << std::endl;
            
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            
            framebuffers["GBuffer"] = GBuffer;
            
            quad = SunTexturedQuad();
            quad.setUpGL();
            
            // Set up shader map
            shaderMap["solid"] = SunShader("./Graphics/Shaders/DeferredShadingPassOneMaterial.vert", "./Graphics/Shaders/DeferredShadingPassOneMaterial.frag");
            shaderMap["textured"] = SunShader("./Graphics/Shaders/DeferredShadingPassOneTexture.vert", "./Graphics/Shaders/DeferredShadingPassOneTexture.frag");
            
            shaderMap["final"] = SunShader("./Graphics/Shaders/DeferredShadingPassTwo.vert", "./Graphics/Shaders/DeferredShadingPassTwo.frag");
        }
    }
    
    void swapBuffers() {
        // Swap the buffers
        glfwSwapBuffers(window);
    }
    
private:
    
};

#endif