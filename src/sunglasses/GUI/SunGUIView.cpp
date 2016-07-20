// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/SunGUIView.h>

#include <sunglasses/GUI/SunGUIRenderer.h>
#include <sunglasses/GUI/SunGUIWindow.h>

SunGUIView::SunGUIView(glm::ivec2 _position,
        glm::ivec2 _size,
        glm::vec4 color,
        bool _visible) : position(_position), size(_size), backgroundColor(color),
        background(position, size), visible(_visible) {

}


void SunGUIView::draw(SunGUIRenderer &renderer) {
    renderer.drawRect(background, backgroundColor);
    for (auto &view : subviews)
        view->draw(renderer);
}

void SunGUIView::addSubview(SunGUIView *subview) {
    subviews.push_back(subview);
}
