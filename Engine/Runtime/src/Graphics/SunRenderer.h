// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNRENDERER_H
#define SUNRENDERER_H

#include <iostream>

#include "SunRenderingNode.h"
#include "SunTexturedQuad.h"
#include "SunPrimitives.h"
#include "SunCamera.h"

class SunScene;

class SunRenderer : public SunBase {
public:
    SunRenderer() { }

    void render();
    void swapBuffers();
	virtual void init();

	inline void setSceneNode(SunScene *s) { scene = s; }

    inline SunRenderingNode * getRootRenderNode() { return rootRenderNode; }
    inline void setRootRenderNode(SunRenderingNode *_root) { rootRenderNode = _root; }

	inline SunNode * getRenderingNodeForString(std::string string) { return renderingNodeMap[string]; }
	inline void addRenderingNodeForString(SunNode *node, std::string string) { renderingNodeMap[string] = node; }

	inline void setWindow(GLFWwindow *w) { window = w; }
protected:
	// Scene Objects
	SunScene *scene;
    SunRenderingNode *rootRenderNode;

	std::map<std::string, SunNode *> renderingNodeMap;
private:
	GLFWwindow *window;
};

#endif
