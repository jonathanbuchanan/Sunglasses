// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "GameRenderer.h"

void GameRenderer::init() {
    SunRenderer::init();

    std::vector<SunRenderNodeSceneTexture> rootTextures = {
        SunRenderNodeSceneTexture("position", GL_RGB16F, GL_RGB, GL_FLOAT),
        SunRenderNodeSceneTexture("normal", GL_RGB16F, GL_RGB, GL_FLOAT),
        SunRenderNodeSceneTexture("_color", GL_RGB, GL_RGB, GL_UNSIGNED_BYTE)
    };
    std::shared_ptr<SunRenderNodeScene> gbuffer = std::shared_ptr<SunRenderNodeScene>(new SunRenderNodeScene(scene->getRoot(), rootTextures));
    gbuffer->setSize(glm::vec2(800.0f, 600.0f));
    gbuffer->addShader("textured", SunShader({
        {"../../Engine/Shaders/Deferred/Scene.vert", SunShaderSourceTypeVertex},
        {"../../Engine/Shaders/Deferred/Textured/Scene.frag", SunShaderSourceTypeFragment}
    }));
    gbuffer->addShader("solid", SunShader({
        {"../../Engine/Shaders/Deferred/Scene.vert", SunShaderSourceTypeVertex},
        {"../../Engine/Shaders/Deferred/Solid/Scene.frag", SunShaderSourceTypeFragment}
    }));
    gbuffer->init();
    root->addSubNode(gbuffer);

    std::shared_ptr<SunShadowMapRenderNode> shadows = std::shared_ptr<SunShadowMapRenderNode>(new SunShadowMapRenderNode(scene->getRoot()));
    shadows->addShader("shadow_directional_light", SunShader({
        {"../../Engine/Shaders/Shadow Map/Directional/Scene.vert", SunShaderSourceTypeVertex},
        {"../../Engine/Shaders/Shadow Map/Directional/Scene.frag", SunShaderSourceTypeFragment}
    }));
    shadows->addShader("shadow_point_light", SunShader({
        {"../../Engine/Shaders/Shadow Map/Point/Scene.vert", SunShaderSourceTypeVertex},
        {"../../Engine/Shaders/Shadow Map/Point/Scene.geom", SunShaderSourceTypeGeometry},
        {"../../Engine/Shaders/Shadow Map/Point/Scene.frag", SunShaderSourceTypeFragment}
    }));
    shadows->init();
    root->addSubNode(shadows);

    std::vector<SunRenderNodeSceneTexture> finalTextures = {

    };
    SunTexturedQuad *quad = new SunTexturedQuad();
    quad->init();
    std::shared_ptr<SunRenderNodeScene> final = std::shared_ptr<SunRenderNodeScene>(new SunRenderNodeScene(quad, scene->getRoot(), finalTextures));
    final->setSize(glm::vec2(800.0f, 600.0f));
    final->setDrawToScreen(true);
    final->addShader("quad", SunShader({
        {"../../Engine/Shaders/Deferred/Quad.vert", SunShaderSourceTypeVertex},
        {"../../Engine/Shaders/Deferred/BlinnPhong/Quad.frag", SunShaderSourceTypeFragment}
    }));
    final->init();
    gbuffer->addSubNode(final);
    shadows->addSubNode(final);
}
