// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/SunGUIView.h>

#include <sunglasses/GUI/SunGUIPath.h>
#include <sunglasses/GUI/SunGUIWindow.h>

SunGUIView::SunGUIView(glm::ivec2 _position,
        glm::ivec2 _size,
        glm::vec4 color,
        bool _visible) : position(_position), backgroundColor(color),
        size(_size), visible(_visible) {

}


void SunGUIView::draw(SunGUIWindow &window) {
    SunGUIPathOperator::PointAt point(glm::ivec2(500, 500));
    SunGUIPath path(
        point
    );
}
