// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIBUTTON_H
#define SUNGUIBUTTON_H

#include <sunglasses/GUI/SunGUIView.h>

/// A button in the GUI
class SunGUIButton : public SunGUIView {
public:
    /// Constructs a button with its various colors
    SunGUIButton(glm::ivec2 origin, glm::ivec2 size, const SunGUIDrawable &drawable/*,
        glm::vec4 _color, glm::vec4 _highlightedColor, glm::vec4 _selectedColor*/);
protected:
    /// Updates the button
    virtual void update(glm::ivec2 parentPosition, SunGUIUpdateInfo info);
/*private:
    /// The color of the button
    glm::vec4 color;

    /// The highlighted (moused over) color of the button
    glm::vec4 highlightedColor;

    /// The selected (clicked on) color of the button
    glm::vec4 selectedColor;*/
};

#endif
