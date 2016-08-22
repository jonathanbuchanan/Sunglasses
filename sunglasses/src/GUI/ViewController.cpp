// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/ViewController.h>

#include <sunglasses/GUI/Window.h>

namespace sunglasses {
namespace GUI {

ViewController::ViewController(Window &window, const Drawable &drawable) :
    view(glm::ivec2(0, 0), glm::ivec2(window.size()), drawable, true) {

}

} // namespace
} // namespace
