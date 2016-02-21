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

class SunScene;

class SunRenderer : public SunBase {
public:
    SunRenderer() { }
    
    void render();
    void swapBuffers();
	virtual void initialize();
    
	inline void setSceneNode(SunScene *s) { scene = s; }

    inline SunRenderingNode * getRootRenderNode() { return rootRenderNode; }
    inline void setRootRenderNode(SunRenderingNode *_root) { rootRenderNode = _root; }

	inline void setWindow(GLFWwindow *w) { window = w; }
protected:
	// Scene Objects
	SunScene *scene;
    SunRenderingNode *rootRenderNode;
	
private:
	GLFWwindow *window;
};

#endif
