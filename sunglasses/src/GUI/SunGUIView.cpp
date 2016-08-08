// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/SunGUIView.h>

#include <sunglasses/GUI/SunGUIRenderer.h>
#include <sunglasses/GUI/SunGUIWindow.h>

SunGUIView::SunGUIView(glm::ivec2 _position,
        glm::ivec2 _size,
        const SunGUIDrawable &_drawable,
        bool _visible) : position(_position), size(_size), drawable(_drawable.copy()),
        visible(_visible), state(SunGUIControlState::Normal) {

}

void SunGUIView::updateTree(glm::ivec2 parentPosition, SunGUIUpdateInfo info) {
    this->update(parentPosition, info);

    glm::ivec2 absolute = parentPosition + (glm::ivec2)position;

    // Update all the subviews
    for (auto &view : subviews)
        view->updateTree(absolute, info);
}

void SunGUIView::update(glm::ivec2 parentPosition, SunGUIUpdateInfo info) {
    glm::ivec2 absolute = parentPosition + (glm::ivec2)position;
    glm::ivec2 cursor = info.cursor;
    if ((absolute.x <= cursor.x && cursor.x <= absolute.x + size.x) &&
        (absolute.y <= cursor.y && cursor.y <= absolute.y + size.y)) {
        if (info.leftMouseButton == SunGUIWindowButtonState::Pressed)
            state = SunGUIControlState::Selected;
        else
            state = SunGUIControlState::Highlighted;
    } else {
        state = SunGUIControlState::Normal;
    }
}

void SunGUIView::drawTree(glm::ivec2 parentPosition, SunGUIRenderer &renderer) {
    if (!visible)
        return;

    glm::ivec2 absolute = parentPosition + (glm::ivec2)position;

    this->draw(parentPosition, renderer);

    for (auto &view : subviews)
        view->drawTree(absolute, renderer);
}

void SunGUIView::draw(glm::ivec2 parentPosition, SunGUIRenderer &renderer) {
    glm::ivec2 absolute = parentPosition + (glm::ivec2)position;
    renderer.drawRect(absolute, size, drawable.get());
}

void SunGUIView::addSubview(SunGUIView *subview) {
    subviews.push_back(subview);
}
