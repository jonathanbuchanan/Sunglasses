// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "GUIMainMenu.h"

unsigned char imageData[] = {
    255, 255, 0, 0, 255, 255, 0, 0,
    0, 255, 0, 0, 0, 255
};

GUIMainMenu::GUIMainMenu(Window &window) :
        Controller(window, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
        v(glm::ivec2(50, 50), glm::ivec2(100, 100), glm::vec4(1.0f)),
        tex(Image(glm::ivec2(2, 2), imageData), TextureMinification::Nearest, TextureMagnification::Nearest),
        image(glm::ivec2(150, 150), glm::ivec2(300, 300), tex),
        button(glm::ivec2(25, 200), glm::ivec2(30, 30), glm::vec4(1.0f), glm::vec4(0.5f), glm::vec4(0.0f)),
        buttonpress([](){std::cout<<"pressed"<<std::endl;}) {
    panel.addChild(&v);
    panel.addChild(&image);
    panel.addChild(&button);

    connect(button.signal_selected, buttonpress);
}
