// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef MOUSEBUTTONMANAGER_H
#define MOUSEBUTTONMANAGER_H

#include "../Core/Base.h"
#include "../Core/Service.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <array>

namespace sunglasses {

class MouseButtonManager : public Service {
public:

    MouseButtonManager();
    MouseButtonManager(GLFWwindow *_window);

    void initialize(GLFWwindow *_window);
    void update();

    void subscribe(Base *subscriber, int button, ButtonEvent event);

    ButtonState pollButton(int button);

    GLFWwindow *window;
private:
    std::vector<std::tuple<Base *, int, ButtonEvent>> subscribers;
    std::array<int, 8> buttons;
};

} // namespace

#endif
