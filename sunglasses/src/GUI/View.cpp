// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/View.h>

#include <sunglasses/GUI/Renderer.h>
#include <sunglasses/GUI/Window.h>

namespace sunglasses {
namespace GUI {

View::View(glm::ivec2 _position,
        glm::ivec2 _size,
        const Drawable &_drawable,
        bool _visible) : position(_position), size(_size), drawable(_drawable.copy()),
        visible(_visible), state(ControlState::Normal) {

}

void View::updateTree(glm::ivec2 parentPosition, UpdateInfo info) {
    this->update(parentPosition, info);

    glm::ivec2 absolute = parentPosition + (glm::ivec2)position;

    // Update all the subviews
    for (auto &view : subviews)
        view->updateTree(absolute, info);
}

void View::update(glm::ivec2 parentPosition, UpdateInfo info) {
    glm::ivec2 absolute = parentPosition + (glm::ivec2)position;
    glm::ivec2 cursor = info.cursor;
    if ((absolute.x <= cursor.x && cursor.x <= absolute.x + size.x) &&
        (absolute.y <= cursor.y && cursor.y <= absolute.y + size.y)) {
        if (info.leftMouseButton == WindowButtonState::Pressed)
            state = ControlState::Selected;
        else
            state = ControlState::Highlighted;
    } else {
        state = ControlState::Normal;
    }
}

void View::drawTree(glm::ivec2 parentPosition, Renderer &renderer) {
    if (!visible)
        return;

    glm::ivec2 absolute = parentPosition + (glm::ivec2)position;

    this->draw(parentPosition, renderer);

    for (auto &view : subviews)
        view->drawTree(absolute, renderer);
}

void View::draw(glm::ivec2 parentPosition, Renderer &renderer) {
    glm::ivec2 absolute = parentPosition + (glm::ivec2)position;
    renderer.drawRect(absolute, size, drawable.get());
}

void View::addSubview(View *subview) {
    subviews.push_back(subview);
}

} // namespace
} // namespace
