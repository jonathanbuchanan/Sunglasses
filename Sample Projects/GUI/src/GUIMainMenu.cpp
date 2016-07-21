// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "GUIMainMenu.h"

GUIMainMenu::GUIMainMenu(SunGUIWindow &window) :
    SunGUIViewController(window, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
    v(glm::ivec2(5, 5), glm::ivec2(100, 100), glm::vec4(1.0f)),
    button(glm::ivec2(150, 150), glm::ivec2(50, 50), glm::vec4(1.0f), glm::vec4(0.0f), glm::vec4(glm::vec3(0.5f), 1.0f)) {
    view.addSubview(&v);
    view.addSubview(&button);
}
