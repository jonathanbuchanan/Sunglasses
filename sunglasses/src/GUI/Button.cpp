// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/Button.h>

namespace sunglasses {
namespace GUI {

Button::Button(glm::ivec2 origin, glm::ivec2 size, const Drawable &drawable/*,
    glm::vec4 _color, glm::vec4 _highlightedColor, glm::vec4 _selectedColor*/) :
    View(origin, size, drawable)/*,
    color(_color), highlightedColor(_highlightedColor), selectedColor(_selectedColor)*/ {

}

//void Button::update(glm::ivec2 parentPosition, UpdateInfo info) {
//    View::update(parentPosition, info);
    
    /// Change the color of the view based on the state
    /*switch (state) {
        case ControlState::Normal:
            backgroundColor = color;
            break;
        case ControlState::Highlighted:
            backgroundColor = highlightedColor;
            break;
        case ControlState::Selected:
            backgroundColor = selectedColor;
            break;
    }*/
//}

} // namespace
} // namespace
