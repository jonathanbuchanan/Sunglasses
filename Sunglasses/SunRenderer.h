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

#include "SunHDRRenderer.h"

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
    GLFWwindow *window;
    
    GLfloat screenWidth;
    GLfloat screenHeight;
    
    SunHDRRenderer HDRrenderer;
    SunGUIRenderer GUIRenderer;
    SunDirectionalLightShadowMapRenderer shadowMapRenderer;
    
    SunTexturedQuad quad;
    
    SunScene *scene;
    SunCamera camera;
    
    map<string, SunShader> shaderMap;
    
    SunObject *watch;
    
    SunDirectionalLightObject *dlight;
    SunObject *plane;
    
    void cycle(map<int, SunButtonState> _buttons, GLfloat deltaTime) {
        // Update the scene
        scene->update(_buttons);
        
        // Clear
        clear();
        
        // Render the scene
        HDRrenderer.renderScene(scene, deltaTime, shaderMap);
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        clear();
        
        quad.render(HDRrenderer.colorBuffer);
        
        // Load the fonts if they aren't loaded
        if (scene->GUIsystem->fontsLoaded == false)
            scene->GUIsystem->loadFonts(&GUIRenderer.textRenderer);
        
        // Render the GUI
        scene->renderGUISystem(&GUIRenderer.textRenderer);
        
        // Swap the buffers
        swapBuffers();
    }
    
    void renderFullscreenQuad(GLuint _texture) {
        
    }
    
    void initialize() {
        // Set up the HDR renderer
        HDRrenderer = SunHDRRenderer();
        HDRrenderer.initialize();
        
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
        shaderMap["solid"] = SunShader("BlinnPhongMaterialBoneless.vert", "BlinnPhongMaterialBoneless.frag");
        shaderMap["textured"] = SunShader("BlinnPhongTextureBoneless.vert", "BlinnPhongTextureBoneless.frag");
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
