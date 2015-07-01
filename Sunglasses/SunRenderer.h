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

#include "SunScene.h"
#include "SunCamera.h"
#include "SunButtonState.h"

class SunRenderer {
public:
    GLFWwindow *window;
    
    GLfloat screenWidth;
    GLfloat screenHeight;
    
    SunGUIRenderer GUIRenderer;
    SunDirectionalLightShadowMapRenderer shadowMapRenderer;
    
    SunScene *scene;
    
    SunShader shader;
    
    SunObject *watch;
    
    SunDirectionalLightObject *dlight;
    SunObject *plane;
    
    void cycle(map<int, SunButtonState> _buttons, GLfloat deltaTime) {
        scene->update(_buttons);
        
        // Clear
        clear();
        
        //shadowMapRenderer.renderDirectionalLight(dlight, deltaTime, glm::vec3(0.0, 0.0, 0.0), scene);
        
        /*glViewport(0, 0, screenWidth * 2, screenHeight * 2);
        clear();*/
        
        // Use the shader
        shader.use();
        
        glActiveTexture(GL_TEXTURE15);
        glBindTexture(GL_TEXTURE_2D, shadowMapRenderer.depthMap);
        glUniform1i(glGetUniformLocation(shader.program, "shadowMap"), 15);
        
        shadowMapRenderer.passLightSpaceMatrix(shader, dlight, glm::vec3(0.0, 0.0, 0.0));
        
        // Pass the matrix uniforms
        scene->camera.setUpMatrixUniforms(shader, screenWidth / screenHeight);
        
        // Pass the camera uniforms
        scene->camera.passPerFrameUniforms(shader);
        
        // Make the scene pass per-frame uniforms
        scene->passPerFrameUniforms(shader);
        
        // Render the scene
        scene->render(shader, deltaTime);
        
        // Render GUI
        GUIRenderer.renderSystem(&scene->GUIsystem);
        
        // Swap the buffers
        swapBuffers();
    }
    
    void initialize() {
        // Set up the GUI renderer
        GUIRenderer = SunGUIRenderer();
        GUIRenderer.initialize();
        
        // Set up the shadow map renderer
        shadowMapRenderer = SunDirectionalLightShadowMapRenderer();
        shadowMapRenderer.initialize();
        
        scene = new SunScene("SceneDemo.xml", window);
        
        // Set up shader
        shader = SunShader("BlinnPhongMaterialBoneless.vert", "BlinnPhongMaterialBoneless.frag");
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
