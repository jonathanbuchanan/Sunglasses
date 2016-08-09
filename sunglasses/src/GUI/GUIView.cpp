// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/GUIView.h>

#include <sunglasses/GUI/GUIRenderer.h>
#include <sunglasses/GUI/GUIWindow.h>

namespace sunglasses {

GUIView::GUIView(glm::ivec2 _position,
        glm::ivec2 _size,
        const GUIDrawable &_drawable,
        bool _visible) : position(_position), size(_size), drawable(_drawable.copy()),
        visible(_visible), state(GUIControlState::Normal) {

}

void GUIView::updateTree(glm::ivec2 parentPosition, GUIUpdateInfo info) {
    this->update(parentPosition, info);

    glm::ivec2 absolute = parentPosition + (glm::ivec2)position;

    // Update all the subviews
    for (auto &view : subviews)
        view->updateTree(absolute, info);
}

void GUIView::update(glm::ivec2 parentPosition, GUIUpdateInfo info) {
    glm::ivec2 absolute = parentPosition + (glm::ivec2)position;
    glm::ivec2 cursor = info.cursor;
    if ((absolute.x <= cursor.x && cursor.x <= absolute.x + size.x) &&
        (absolute.y <= cursor.y && cursor.y <= absolute.y + size.y)) {
        if (info.leftMouseButton == GUIWindowButtonState::Pressed)
            state = GUIControlState::Selected;
        else
            state = GUIControlState::Highlighted;
    } else {
        state = GUIControlState::Normal;
    }
}

void GUIView::drawTree(glm::ivec2 parentPosition, GUIRenderer &renderer) {
    if (!visible)
        return;

    glm::ivec2 absolute = parentPosition + (glm::ivec2)position;

    this->draw(parentPosition, renderer);

    for (auto &view : subviews)
        view->drawTree(absolute, renderer);
}

void GUIView::draw(glm::ivec2 parentPosition, GUIRenderer &renderer) {
    glm::ivec2 absolute = parentPosition + (glm::ivec2)position;
    renderer.drawRect(absolute, size, drawable.get());
}

void GUIView::addSubview(GUIView *subview) {
    subviews.push_back(subview);
}

} // namespace
