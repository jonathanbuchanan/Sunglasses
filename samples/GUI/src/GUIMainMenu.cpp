// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "GUIMainMenu.h"

GUIMainMenu::GUIMainMenu(Window &window) :
        ViewController(window, DrawableSolidColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))),
        v(glm::ivec2(50, 50), glm::ivec2(400, 400), DrawableSolidColor(glm::vec4(1.0f))),
        /*button(glm::ivec2(55, 55), glm::ivec2(50, 50), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec4(0.0f), glm::vec4(glm::vec3(0.5f), 1.0f))*/
        button(glm::ivec2(55, 55), glm::ivec2(50, 50), DrawableSolidColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f))) {
    view.addSubview(&v);
    v.addSubview(&button);
    
}
