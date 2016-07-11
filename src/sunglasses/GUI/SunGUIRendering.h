// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIRENDERING_H
#define SUNGUIRENDERING_H

#include <vector>

#include <glm/glm.hpp>

#include <GL/glew.h>

#include <sunglasses/Graphics/SunShader.h>

class SunGUIWindow;

/// A container used to store shaders for drawing the GUI
struct SunGUIShaderContainer {
    /// Initializes the shaders
    /**
     * @param window The window containing the OpenGL context (has no purpose
     * but to ensure that the context exists)
     */
    SunGUIShaderContainer(SunGUIWindow &window);

    /// The fill shader
    SunShader fill;
};

/// An object that contains vertex data that can be filled
class SunGUIFillPath {
public:
    /// Constructs an object from a set of vertices
    SunGUIFillPath(const std::vector<glm::ivec2> &vertices);
private:
    /// The VBO and VAO
    GLuint VBO, VAO;

    /// The fill shader
    static const SunShader shader;
};

#endif
