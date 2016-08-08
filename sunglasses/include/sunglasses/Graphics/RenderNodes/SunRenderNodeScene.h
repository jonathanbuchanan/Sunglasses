// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNRENDERNODESCENE_H
#define SUNRENDERNODESCENE_H

#include <sunglasses/Graphics/SunRenderNode.h>
#include <sunglasses/Graphics/SunShader.h>

#include <vector>
#include <utility>
#include <glm/glm.hpp>

namespace sunglasses {

class SunRenderNodeScene;

/// A structure that represents a texture belonging to a render node
struct SunRenderNodeSceneTexture {
friend SunRenderNodeScene;
public:
    /// Constructor for the render node texture
    /**
     * @param _name The name of the texture
     * @param _internalFormat The internal format of the texture
     * @param _format The format of the texture
     * @param _type The type of the texture
     */
    SunRenderNodeSceneTexture(std::string _name, GLuint _internalFormat, GLenum _format, GLenum _type);

private:
    /// The texture
    GLuint texture;

    /// The name of the texture
    std::string name;

    /// The internal format of the texture
    GLuint internalFormat;

    /// The format of the texture
    GLenum format;

    /// The type of the texture
    GLenum type;
};

/// A SunRenderNode subclass that renders a scene
/**
 * SunRenderNodeScene is a subclass of SunRenderNode that renders a scene.
 * It will always write to a framebuffer, but you can use it in combination with
 * the SunRenderNodeEnd render node to draw to the screen. This class is usable
 * in most situations, such as forward shading, deferred shading, SSAO, etc.
 * different types of render nodes should be used for techniques like shadow mapping.
 */
class SunRenderNodeScene : public SunRenderNode {
public:
    /// A constructor
    /**
     * @param _target The pointer to the render target
     * @param _textures The vector of textures
     */
    SunRenderNodeScene(SunBase *_target, std::vector<SunRenderNodeSceneTexture> _textures);

    /// A constructor
    /**
     * @param _target The pointer to the render target
     * @param _uniformTarget The pointer to the uniform target
     * @param _textures The vector of textures
     */
    SunRenderNodeScene(SunBase *_target, SunBase *_uniformTarget, std::vector<SunRenderNodeSceneTexture> _textures);

    /// Initializes the render node
    /**
     * This member function initializes the render node by creating the framebuffer
     * and all of its attachments.
     * @warning Size must be assigned.
     */
    virtual void init();

    /// Renders the scene.
    /**
     * This function renders the scene. It iterates through each shader, using the tag
     * system, and sends a 'render' action to the root of the scene graph.
     * @warning Root must be assigned.
     */
    virtual void render(SunAction action);

    /// Binds the outputs for the next render node.
    /**
     * This member function binds the outputs (textures) for the next render node
     * to work with.
     * @warning The 'shader' parameter must contain a pointer to the shader to bind to
     */
    virtual void bindOutputs(SunAction action);

    /// Adds a shader for the given tag.
    void addShader(std::string tag, SunShader shader);

    /// Sets the vector of shaders.
    void setShaders(std::vector<std::pair<std::string, SunShader>> _shaders);

    /// Sets the target pointer.
    void setTarget(SunBase *_target);

    /// Sets the uniform target
    void setUniformTarget(SunBase *_uniformTarget);

    /// Sets the drawToScreen boolean.
    void setDrawToScreen(bool _d) { drawToScreen = _d; }

    /// Sets the size vec2.
    void setSize(glm::vec2 _size);
private:
    /// A vector of pairs of tags and shaders
    /**
     * At render time, a render action is sent out that has a tag for each respective
     * shader. This way, you can specify different shaders for different object by
     * choosing tags.
     */
    std::vector<std::pair<std::string, SunShader>> shaders;

    /// A pointer to the target to render
    SunBase *target;

    /// A pointer to the target for passing uniforms
    SunBase *uniformTarget;

    /// A boolean that determines whether the render node draws to the screen
    bool drawToScreen = false;

    /// The framebuffer object
    GLuint fbo;

    /// The renderbuffer object
    GLuint rbo;

    /// The vector of textures
    /**
     * @warning The textures will be attached in the order that they are in this
     * vector. A texture that should attached with GL_COLOR_ATTACHMENT0 should be first
     * in the vector.
     */
    std::vector<SunRenderNodeSceneTexture> textures;

    /// The size of the buffer in pixels
    glm::vec2 size;
};

} // namespace

#endif
