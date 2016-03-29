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

    void setSceneNode(SunScene *s) { scene = s; }

    std::shared_ptr<SunNode> getRootRenderNode() { return rootRenderNode; }
    void setRootRenderNode(std::shared_ptr<SunNode> _root) { rootRenderNode = _root; }

    std::shared_ptr<SunNode> getRenderingNodeForString(std::string string) { return renderingNodeMap[string]; }
    void addRenderingNodeForString(std::shared_ptr<SunNode> node, std::string string) { renderingNodeMap[string] = node; }

    void setWindow(GLFWwindow *w) { window = w; }
protected:
    // Scene Objects
    SunScene *scene;
    std::shared_ptr<SunNode> rootRenderNode;

    std::map<std::string, std::shared_ptr<SunNode>> renderingNodeMap;
private:
    GLFWwindow *window;
};

#endif
