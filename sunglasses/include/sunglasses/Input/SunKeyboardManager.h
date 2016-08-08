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

namespace sunglasses {

class SunScript;

class SunKeyboardManager : public SunService {
public:
    SunKeyboardManager();
    SunKeyboardManager(GLFWwindow *_window);

    void initialize(GLFWwindow *_window);
    void update();
    
    /// Registers the service in a script
    /**
     * @param script A pointer to the script
     */
    void registerWithScript(SunScript *script);

    void subscribe(SunBase *subscriber, int key, SunButtonEvent event);

    SunButtonState pollKey(int key);
    bool keyDown(int key);

    GLFWwindow *window;
private:
    std::vector<std::tuple<SunBase *, int, SunButtonEvent>> subscribers;
    std::array<int, 512> keys;
};

} // namespace

#endif
