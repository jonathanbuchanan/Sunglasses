// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNRENDERER_H
#define SUNRENDERER_H

#include <iostream>

#include "SunRenderNode.h"
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

	void setSceneNode(SunScene *s) { scene = s; }
protected:
	// Scene Objects
	SunScene *scene;
    SunNode *root;

	std::map<std::string, SunNode *> renderingNodeMap;
};

#endif
