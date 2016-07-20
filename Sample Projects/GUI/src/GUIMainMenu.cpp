// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "GUIMainMenu.h"

GUIMainMenu::GUIMainMenu(SunGUIWindow &window) :
    SunGUIViewController(window, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
    v(glm::ivec2(5, 5), glm::ivec2(100, 100), glm::vec4(1.0f)) {
    view.addSubview(v);
}
