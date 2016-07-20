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
    SunGUIRenderer(SunGUIWindow &_window);

    /// Renders a rectangle
    void drawRect(const SunGUIRect &rect, glm::vec4 color);
private:
    /// The window
    SunGUIWindow &window;

    /// The fill shader
    SunShader fillShader;
};

#endif
