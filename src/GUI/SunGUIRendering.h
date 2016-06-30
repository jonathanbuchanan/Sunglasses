// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIRENDERING_H
#define SUNGUIRENDERING_H

#include <glm/glm.hpp>

/// Draws a rectangle with the specified center, dimensions, and color
/**
 * This function draws a rectangle with a specific center, size, color.
 * The color includes an alpha channel.
 * @param center The center of the rectangle
 * @param size The size of the rectangle
 * @param color The color of the rectangle (including alpha)
 */
extern void drawRectangle(glm::vec2 center, glm::vec2 size, glm::vec4 color);

#endif
