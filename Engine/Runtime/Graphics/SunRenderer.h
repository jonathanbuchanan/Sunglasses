// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef OpenGL_Test_3_Renderer_h
#define OpenGL_Test_3_Renderer_h

#include <iostream>

#include "./SunTextRenderer.h"
#include "./SunRenderingNode.h"
#include "./SunTexturedQuad.h"
#include "./SunPrimitives.h"
#include "./SunCamera.h"
#include "SunButtonState.h"

class SunRenderer {
public:
    SunRenderer() { }
    
    void render(GLfloat _deltaTime);
    void swapBuffers();
    
    inline GLFWwindow * getWindow() { return window; }
    inline void setWindow(GLFWwindow *_window) { window = _window; }
    
    inline GLfloat & getScreenWidth() { return screenWidth; }
    inline GLfloat & getScreenHeight() { return screenHeight; }
    inline void setScreenWidth(GLfloat width) { screenWidth = width; }
    inline void setScreenHeight(GLfloat height) { screenHeight = height; }
    
    inline SunNode * getSceneNode() { return scene; }
    inline void setSceneNode(SunNode *_scene) { scene = _scene; }
    
    inline SunRenderingNode * getRootRenderNode() { return rootRenderNode; }
    inline void setRootRenderNode(SunRenderingNode *_root) { rootRenderNode = _root; }
protected:
	// Scene Objects
    SunNode *scene;
    SunRenderingNode *rootRenderNode;
	
private:
    // Window and window size
    GLFWwindow *window;

    GLfloat screenWidth;
    GLfloat screenHeight;
};

#endif
