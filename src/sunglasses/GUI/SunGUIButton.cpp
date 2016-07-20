// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/SunGUIButton.h>

SunGUIButton::SunGUIButton(glm::ivec2 origin, glm::ivec2 size,
    glm::vec4 _color, glm::vec4 _highlightedColor, glm::vec4 _selectedColor) :
    color(_color), highlightedColor(_highlightedColor), selectedColor(_selectedColor),
    SunGUIView(origin, size, color) {

}
