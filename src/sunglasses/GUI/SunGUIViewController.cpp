// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/SunGUIViewController.h>

#include <sunglasses/GUI/SunGUIWindow.h>

SunGUIViewController::SunGUIViewController(SunGUIWindow &window) :
    view(glm::ivec2(0, 0), glm::ivec2(window.size()), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), true) {

}
