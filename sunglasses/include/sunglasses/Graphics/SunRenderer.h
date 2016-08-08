// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNRENDERER_H
#define SUNRENDERER_H

#include <iostream>

#include <sunglasses/Graphics/SunRenderNode.h>
#include <sunglasses/Graphics/SunTexturedQuad.h>
#include <sunglasses/Graphics/SunPrimitives.h>
#include <sunglasses/Graphics/SunCamera.h>

namespace sunglasses {

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

} // namespace

#endif
