// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNRENDERNODESCENE_H
#define SUNRENDERNODESCENE_H

#include "../SunRenderNode.h"
#include "../SunShader.h"

#include <vector>
#include <utility>
#include <glm/glm.hpp>

/// A SunRenderNode subclass that renders a 3D scene
/**
 * SunRenderNodeScene is a subclass of SunRenderNode that renders a 3D scene.
 * It will always write to a framebuffer, but you can use it in combination with
 * the SunRenderNodeEnd render node to draw to the screen.
 *
 */
class SunRenderNodeScene : public SunRenderNode {
public:
    /// The default constructor
    SunRenderNodeScene();

    /// The constructor for root
    /**
     * @param _root The pointer to the scene's root node
     */
    SunRenderNodeScene(SunNode *_root);

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
     */
    virtual void bindOutputs();

    /// Adds a shader for the given tag.
    void addShader(std::string tag, SunShader shader);

    /// Sets the vector of shaders.
    void setShaders(std::vector<std::pair<std::string, SunShader>> _shaders);

    /// Sets the root node pointer.
    void setRoot(SunNode *_root);

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

    /// A pointer to the root node of the scene
    SunNode *root;

    /// The framebuffer object
    GLuint fbo;

    /// The renderbuffer object
    GLuint rbo;

    /// The size of the buffer in pixels
    glm::vec2 size;
};


#endif
