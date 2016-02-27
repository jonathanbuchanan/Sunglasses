// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNKEYBOARDMANAGER_H
#define SUNKEYBOARDMANAGER_H

#include "../Core/SunBase.h"
#include "../Core/SunService.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <array>
#include <iostream>

class SunKeyboardManager : public SunService {
public:

    SunKeyboardManager();
    SunKeyboardManager(GLFWwindow *_window);

    void initialize(GLFWwindow *_window);
    void update();

    void subscribe(SunBase *subscriber, int key, SunButtonEvent event);

    SunButtonState pollKey(int key);

    GLFWwindow *window;
private:
    std::vector<std::tuple<SunBase *, int, SunButtonEvent>> subscribers;
    std::array<int, 512> keys;
};

#endif
