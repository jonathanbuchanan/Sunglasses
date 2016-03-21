// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunRenderNodeScene.h"

#include "../SunWindowManager.h"
#include "../SunPrimitives.h"

SunRenderNodeScene::SunRenderNodeScene() {

}

SunRenderNodeScene::SunRenderNodeScene(SunNode *_root) : root(_root) {

}

void SunRenderNodeScene::init() {
    SunRenderNode::init();

    glGenFramebuffers(1, &fbo); // Generate the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, fbo); // Bind the framebuffer
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind any leftover textures

    glGenRenderbuffers(1, &rbo); // Generate the renderbuffer
    glBindRenderbuffer(GL_RENDERBUFFER, rbo); // Bind the renderbuffer
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y); // Generate the renderbuffer storage
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo); // Attach the renderbuffer to the framebuffer as a depth attachment

    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind the framebuffer
}

void SunRenderNodeScene::render(SunAction action) {
    float delta = ((SunWindowManager *)getService("window_manager"))->getDelta();
    //glBindFramebuffer(GL_FRAMEBUFFER, fbo); // Bind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // TEMPORARY
    clear();
    for (size_t i = 0; i < shaders.size(); ++i) { // Iterate through shaders
        shaders[i].second.use(shaders[i].first, delta, root); // Render with each shader
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind the framebuffer
}

void SunRenderNodeScene::bindOutputs() {

}

void SunRenderNodeScene::addShader(std::string tag, SunShader shader) {
    shaders.push_back(std::make_pair(tag, shader));
}

void SunRenderNodeScene::setShaders(std::vector<std::pair<std::string, SunShader>> _shaders) {
    shaders = _shaders;
}

void SunRenderNodeScene::setRoot(SunNode *_root) {
    root = _root;
}

void SunRenderNodeScene::setSize(glm::vec2 _size) {
    size = _size;
}
