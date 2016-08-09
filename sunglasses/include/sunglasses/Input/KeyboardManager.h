// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include "../Core/Base.h"
#include "../Core/Service.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <array>
#include <iostream>

namespace sunglasses {

class Script;

class KeyboardManager : public Service {
public:
    KeyboardManager();
    KeyboardManager(GLFWwindow *_window);

    void initialize(GLFWwindow *_window);
    void update();
    
    /// Registers the service in a script
    /**
     * @param script A pointer to the script
     */
    void registerWithScript(Script *script);

    void subscribe(Base *subscriber, int key, ButtonEvent event);

    ButtonState pollKey(int key);
    bool keyDown(int key);

    GLFWwindow *window;
private:
    std::vector<std::tuple<Base *, int, ButtonEvent>> subscribers;
    std::array<int, 512> keys;
};

} // namespace

#endif
