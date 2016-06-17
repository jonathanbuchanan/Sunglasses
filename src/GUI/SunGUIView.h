// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIVIEW_H
#define SUNGUIVIEW_H

#include <glm/glm.hpp>

/// A view in the GUI toolkit
class SunGUIView {
public:
    bool isVisible() const { return visible; }
    void show() { visible = true; }
    void hide() { visible = false; }

    void setBackgroundColor(glm::vec3 b) { backgroundColor = b; }
private:
    /// The visibility of the view
    /**
     * The object is displayed when visible, but hidden when not.
     */
    bool visible;

    /// The background color of the view
    glm::vec3 backgroundColor;
};

#endif
