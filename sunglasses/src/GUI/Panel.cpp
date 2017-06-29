// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/Panel.h>

namespace sunglasses {
namespace GUI {

Panel::Panel(glm::ivec2 _position, glm::ivec2 _size,
    graphics::ColoredRectangle::Color _background, bool _visible) :
        Control(_position, _size, _visible), background(_background, position, size) {

}

Panel::Panel(const graphics::Window &window, graphics::ColoredRectangle::Color _background,
    bool _visible) :
        Control(glm::ivec2(0, 0), window.getSize(), _visible), background(_background, position, size) {

}

} // namespace
} // namespace
