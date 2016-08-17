// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "GUIMainMenu.h"

unsigned char imageData[] = {
    255, 255, 255, 255, 0, 0,
    0, 255, 0, 0, 0, 255
};
unsigned char *d = imageData;

GUIMainMenu::GUIMainMenu(Window &window) :
        ViewController(window, DrawableSolidColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))),
        v(glm::ivec2(50, 50), glm::ivec2(100, 100), DrawableSolidColor(glm::vec4(1.0f))),
        tex("/home/jonathan/Pictures/TEST.png"),
        image(glm::ivec2(150, 150), glm::ivec2(300, 300), DrawableImage(tex)),
        /*button(glm::ivec2(55, 55), glm::ivec2(50, 50), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec4(0.0f), glm::vec4(glm::vec3(0.5f), 1.0f))*/
        button(glm::ivec2(55, 55), glm::ivec2(50, 50), DrawableSolidColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f))) {
    view.addSubview(&v);
    view.addSubview(&image);
    v.addSubview(&button);
}
