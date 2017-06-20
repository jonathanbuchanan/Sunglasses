// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/RenderNodes/RenderNodeScene.h>

#include <sunglasses/Graphics/WindowManager.h>
#include <sunglasses/Graphics/Primitives.h>

namespace sunglasses {

RenderNodeSceneTexture::RenderNodeSceneTexture(std::string _name, GLuint _internalFormat, GLenum _format, GLenum _type) : name(_name), internalFormat(_internalFormat), format(_format), type(_type) { }



RenderNodeScene::RenderNodeScene(Base *_target, std::vector<RenderNodeSceneTexture> _textures) : target(_target), uniformTarget(_target), textures(_textures) {

}

RenderNodeScene::RenderNodeScene(Base *_target, Base *_uniformTarget, std::vector<RenderNodeSceneTexture> _textures) : target(_target), uniformTarget(_uniformTarget), textures(_textures) {

}


void RenderNodeScene::init() {
    RenderNode::init();

    if (drawToScreen == false) {
        glGenFramebuffers(1, &fbo); // Generate the framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, fbo); // Bind the framebuffer

        GLuint attachments[textures.size()];

        for (size_t i = 0; i < textures.size(); ++i) {
            glGenTextures(1, &textures[i].texture);
            glBindTexture(GL_TEXTURE_2D, textures[i].texture);
            glTexImage2D(GL_TEXTURE_2D, 0, textures[i].internalFormat, size.x, size.y, 0, textures[i].format, textures[i].type, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures[i].texture, 0);
            attachments[i] = GL_COLOR_ATTACHMENT0 + i;
        }

        glDrawBuffers(textures.size(), attachments);

        glGenRenderbuffers(1, &rbo); // Generate the renderbuffer
        glBindRenderbuffer(GL_RENDERBUFFER, rbo); // Bind the renderbuffers
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y); // Generate the renderbuffer storage
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo); // Attach the renderbuffer to the framebuffer as a depth attachment
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind the framebuffer
    } else {
        fbo = 0; // Set the framebuffer to the screen-buffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

void RenderNodeScene::render(Action action) {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo); // Bind the framebuffer
    glViewport(0, 0, size.x, size.y);
    graphics::clear();
    for (size_t i = 0; i < shaders.size(); ++i) { // Iterate through shaders
        shaders[i].second.use();

        Action bind = Action("bindOutputs");
        bind.addParameter("shader", &shaders[i].second);

        sendAction(bind, parent);

        Action uniform("uniform");
        uniform.addParameter("shader", &shaders[i].second);
        uniform.setRecursive(true);
        sendAction(uniform, uniformTarget);

        Action render("render");
        render.setRecursive(true);
        render.addParameter("shader", &shaders[i].second);
        render.addParameter("tag", &shaders[i].first);
        sendAction(render, target);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind the framebuffer
}

void RenderNodeScene::bindOutputs(Action action) {
    graphics::Shader *shader = action.getParameterPointer<graphics::Shader>("shader");
    for (size_t i = 0; i < textures.size(); ++i) {
        int textureUnit = shader->getNextTextureUnit();
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, textures[i].texture);
        (*shader)[textures[i].name] = textureUnit;
    }
}

void RenderNodeScene::addShader(std::string tag, graphics::Shader shader) {
    shaders.push_back(std::make_pair(tag, shader));
}

void RenderNodeScene::setShaders(std::vector<std::pair<std::string, graphics::Shader>> _shaders) {
    shaders = _shaders;
}

void RenderNodeScene::setTarget(Base *_target) {
    target = _target;
}

void RenderNodeScene::setUniformTarget(Base *_uniformTarget) {
    uniformTarget = _uniformTarget;
}

void RenderNodeScene::setSize(glm::vec2 _size) {
    size = _size;
}

} // namespace
