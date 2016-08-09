// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef RENDERNODESCENE_H
#define RENDERNODESCENE_H

#include <sunglasses/Graphics/RenderNode.h>
#include <sunglasses/Graphics/Shader.h>

#include <vector>
#include <utility>
#include <glm/glm.hpp>

namespace sunglasses {

class RenderNodeScene;

/// A structure that represents a texture belonging to a render node
struct RenderNodeSceneTexture {
friend RenderNodeScene;
public:
    /// Constructor for the render node texture
    /**
     * @param _name The name of the texture
     * @param _internalFormat The internal format of the texture
     * @param _format The format of the texture
     * @param _type The type of the texture
     */
    RenderNodeSceneTexture(std::string _name, GLuint _internalFormat, GLenum _format, GLenum _type);

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

/// A RenderNode subclass that renders a scene
/**
 * RenderNodeScene is a subclass of RenderNode that renders a scene.
 * It will always write to a framebuffer, but you can use it in combination with
 * the RenderNodeEnd render node to draw to the screen. This class is usable
 * in most situations, such as forward shading, deferred shading, SSAO, etc.
 * different types of render nodes should be used for techniques like shadow mapping.
 */
class RenderNodeScene : public RenderNode {
public:
    /// A constructor
    /**
     * @param _target The pointer to the render target
     * @param _textures The vector of textures
     */
    RenderNodeScene(Base *_target, std::vector<RenderNodeSceneTexture> _textures);

    /// A constructor
    /**
     * @param _target The pointer to the render target
     * @param _uniformTarget The pointer to the uniform target
     * @param _textures The vector of textures
     */
    RenderNodeScene(Base *_target, Base *_uniformTarget, std::vector<RenderNodeSceneTexture> _textures);

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
    virtual void render(Action action);

    /// Binds the outputs for the next render node.
    /**
     * This member function binds the outputs (textures) for the next render node
     * to work with.
     * @warning The 'shader' parameter must contain a pointer to the shader to bind to
     */
    virtual void bindOutputs(Action action);

    /// Adds a shader for the given tag.
    void addShader(std::string tag, Shader shader);

    /// Sets the vector of shaders.
    void setShaders(std::vector<std::pair<std::string, Shader>> _shaders);

    /// Sets the target pointer.
    void setTarget(Base *_target);

    /// Sets the uniform target
    void setUniformTarget(Base *_uniformTarget);

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
    std::vector<std::pair<std::string, Shader>> shaders;

    /// A pointer to the target to render
    Base *target;

    /// A pointer to the target for passing uniforms
    Base *uniformTarget;

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
    std::vector<RenderNodeSceneTexture> textures;

    /// The size of the buffer in pixels
    glm::vec2 size;
};

} // namespace

#endif
