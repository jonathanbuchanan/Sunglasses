// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/GUIButton.h>

namespace sunglasses {

GUIButton::GUIButton(glm::ivec2 origin, glm::ivec2 size, const GUIDrawable &drawable/*,
    glm::vec4 _color, glm::vec4 _highlightedColor, glm::vec4 _selectedColor*/) :
    GUIView(origin, size, drawable)/*,
    color(_color), highlightedColor(_highlightedColor), selectedColor(_selectedColor)*/ {

}

void GUIButton::update(glm::ivec2 parentPosition, GUIUpdateInfo info) {
    GUIView::update(parentPosition, info);
    
    /// Change the color of the view based on the state
    /*switch (state) {
        case GUIControlState::Normal:
            backgroundColor = color;
            break;
        case GUIControlState::Highlighted:
            backgroundColor = highlightedColor;
            break;
        case GUIControlState::Selected:
            backgroundColor = selectedColor;
            break;
    }*/
}

} // namespace
