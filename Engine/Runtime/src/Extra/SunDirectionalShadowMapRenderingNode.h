// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SunDirectionalShadowMapRenderingNode_h
#define SunDirectionalShadowMapRenderingNode_h

#include "../Graphics/SunRenderingNode.h"

#include "SunDirectionalLight.h"

class SunWindowManager;

class SunDirectionalShadowMapRenderingNode : public SunNode {
public:
    SunDirectionalShadowMapRenderingNode();
    SunDirectionalShadowMapRenderingNode(glm::vec2 _size);
    SunDirectionalShadowMapRenderingNode(glm::vec2 _size, SunDirectionalLight *_light);
    SunDirectionalShadowMapRenderingNode(SunNode *_root);

    virtual void init();
    virtual void render(SunAction action);

    inline SunDirectionalLight * getLight() { return light; }
    inline void setLight(SunDirectionalLight *l) { light = l; }

    inline void setResolution(glm::vec2 r) { resolution = r; }
    inline void setSize(glm::vec2 s) { size = s; }

    inline void setNearPlane(GLfloat n) { nearPlane = n; }
    inline void setFarPlane(GLfloat f) { farPlane = f; }

    inline SunRenderingNodeOutput * getOutput() { return output; }

    inline void setRoot(SunNode *r) { root = r; }
private:
    SunDirectionalLight *light;

    GLuint fbo;

    glm::vec2 resolution;
    glm::vec2 size;

    GLfloat nearPlane = 0.1f;
    GLfloat farPlane = 100.0f;

    SunRenderingNodeOutput *output;
    SunNode *root;
    static SunShader shader;
    static bool shaderInitialized;
};

#endif
