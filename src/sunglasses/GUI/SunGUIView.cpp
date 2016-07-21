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
        visible(_visible), state(SunGUIControlState::Normal) {

}

void SunGUIView::update(SunGUIUpdateInfo info) {
    glm::ivec2 cursor = info.cursor;
    if ((position.x <= cursor.x && cursor.x <= position.x + size.x) &&
        (position.y <= cursor.y && cursor.y <= position.y + size.y)) {
        if (info.leftMouseButton == SunGUIWindowButtonState::Pressed)
            state = SunGUIControlState::Selected;
        else
            state = SunGUIControlState::Highlighted;
    } else {
        state = SunGUIControlState::Normal;
    }

    // Update all the subviews
    for (auto &view : subviews)
        view->update(info);
}

void SunGUIView::draw(SunGUIRenderer &renderer) {
    renderer.drawRect(position, size, backgroundColor);
    for (auto &view : subviews)
        view->draw(renderer);
}

void SunGUIView::addSubview(SunGUIView *subview) {
    subviews.push_back(subview);
}
