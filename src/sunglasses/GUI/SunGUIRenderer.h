// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIRENDERER_H
#define SUNGUIRENDERER_H

#include <vector>

#include <glm/glm.hpp>

#include <GL/glew.h>

#include <sunglasses/Graphics/SunShader.h>
#include <sunglasses/GUI/SunGUIRect.h>

class SunGUIWindow;

/// A container used to store shaders for drawing the GUI
class SunGUIRenderer {
public:
    /// Initializes the shaders
    /**
     * @param window The window containing the OpenGL context (has no purpose
     * but to ensure that the context exists)
     */
    SunGUIRenderer(SunGUIWindow &_window);

    /// Renders a filled path
    void render(const SunGUIRect &rect);
private:
    /// The window
    SunGUIWindow &window;

    /// The fill shader
    SunShader fillShader;
};

#endif
