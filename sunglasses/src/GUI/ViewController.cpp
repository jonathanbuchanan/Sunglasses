// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/ViewController.h>

#include <sunglasses/GUI/Window.h>

namespace sunglasses {

ViewController::ViewController(Window &window, const Drawable &drawable) :
    view(glm::ivec2(0, 0), glm::ivec2(window.size()), drawable, true) {

}

} // namespace
