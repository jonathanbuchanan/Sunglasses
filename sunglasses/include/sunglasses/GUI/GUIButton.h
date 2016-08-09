// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include <sunglasses/GUI/GUIView.h>

namespace sunglasses {

/// A button in the GUI
class GUIButton : public GUIView {
public:
    /// Constructs a button with its various colors
    GUIButton(glm::ivec2 origin, glm::ivec2 size, const GUIDrawable &drawable/*,
        glm::vec4 _color, glm::vec4 _highlightedColor, glm::vec4 _selectedColor*/);
protected:
    /// Updates the button
    virtual void update(glm::ivec2 parentPosition, GUIUpdateInfo info);
/*private:
    /// The color of the button
    glm::vec4 color;

    /// The highlighted (moused over) color of the button
    glm::vec4 highlightedColor;

    /// The selected (clicked on) color of the button
    glm::vec4 selectedColor;*/
};

} // namespace

#endif
