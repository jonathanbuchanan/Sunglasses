// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef BUTTON_H
#define BUTTON_H

#include <sunglasses/GUI/View.h>

namespace sunglasses {

/// A button in the GUI
class Button : public View {
public:
    /// Constructs a button with its various colors
    Button(glm::ivec2 origin, glm::ivec2 size, const Drawable &drawable/*,
        glm::vec4 _color, glm::vec4 _highlightedColor, glm::vec4 _selectedColor*/);
protected:
    /// Updates the button
    virtual void update(glm::ivec2 parentPosition, UpdateInfo info);
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
