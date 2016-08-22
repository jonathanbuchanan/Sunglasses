// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>

#include <sunglasses/Graphics/RenderNode.h>
#include <sunglasses/Graphics/TexturedQuad.h>
#include <sunglasses/Graphics/Primitives.h>
#include <sunglasses/Graphics/Camera.h>

namespace sunglasses {

class Scene;

class Renderer : public Base {
public:
    Renderer() { }

    void render();
    void swapBuffers();
    virtual void init();

    void setSceneNode(Scene *s) { scene = s; }
protected:
    // Scene Objects
    Scene *scene;
    Node *root;

    std::map<std::string, Node *> renderingNodeMap;
};

} // namespace

#endif
