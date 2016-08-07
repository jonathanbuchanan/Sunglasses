// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/SunGUIView.h>

#include <sunglasses/GUI/SunGUIRenderer.h>
#include <sunglasses/GUI/SunGUIWindow.h>

SunGUIView::ConstraintInt::ConstraintInt(rhea::simplex_solver &_solver, int value) :
        solver(_solver), variable(value) {

}

void SunGUIView::ConstraintInt::operator =(int value) {
    std::cout << "____" << value << std::endl;
    std::cout << variable.value() << std::endl;
    variable.set_value(value);
    solver.suggest(variable, value);
    std::cout << variable.value() << std::endl;
}

SunGUIView::ConstraintInt::operator int() {
    return variable.value();
}

SunGUIView::ConstraintInt::operator rhea::linear_expression() {
    return rhea::linear_expression(variable);
}

SunGUIView::vec2::vec2(rhea::simplex_solver &_solver, int _x, int _y) :
        x(_solver, _x), y(_solver, _y) {

}

SunGUIView::vec2::vec2(rhea::simplex_solver &_solver, glm::ivec2 vector) :
        x(_solver, vector.x), y(_solver, vector.y) {

}

void SunGUIView::vec2::operator =(glm::ivec2 vector) {
    x = vector.x;
    y = vector.y;
}

SunGUIView::vec2::operator glm::ivec2() {
    return glm::ivec2((int)x, (int)y);
}

SunGUIView::SunGUIView(glm::ivec2 _position,
        glm::ivec2 _size,
        glm::vec4 color,
        bool _visible) : position(solver, _position), size(solver, _size), backgroundColor(color),
        visible(_visible), state(SunGUIControlState::Normal) {
    solver.add_stay(size.x.variable, rhea::strength::required());
    solver.add_stay(size.y.variable, rhea::strength::required());
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
    renderer.drawRect(absolute, size, backgroundColor);
}

void SunGUIView::addSubview(SunGUIView *subview) {
    subviews.push_back(subview);
}

rhea::linear_expression SunGUIView::expressionForValue(ConstraintValue value) {
    switch (value) {
    case ConstraintValue::Left:
        return position.x;
        break;
    case ConstraintValue::Right:
        return position.x + size.x;
        break;
    case ConstraintValue::Top:
        return position.y;
        break;
    case ConstraintValue::Bottom:
        return position.y + size.y;
        break;
    case ConstraintValue::CenterX:
        return position.x + (size.x / 2);
        break;
    case ConstraintValue::CenterY:
        return position.y + (size.y / 2);
        break;
    case ConstraintValue::Width:
        return size.x;
        break;
    case ConstraintValue::Height:
        return size.y;
        break;
    }
}

rhea::linear_expression SunGUIView::operator[](ConstraintValue value) {
    return expressionForValue(value);
}

void SunGUIView::addConstraint(rhea::constraint constraint) {
    solver.add_constraint(constraint);
}
