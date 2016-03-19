// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunKeyboardManager.h"

SunKeyboardManager::SunKeyboardManager() {

}

SunKeyboardManager::SunKeyboardManager(GLFWwindow *_window) {
    initialize(_window);
}

void SunKeyboardManager::initialize(GLFWwindow *_window) {
    // Set the input mode to sticky keys
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, 1);
    window = _window;
}

void SunKeyboardManager::update() {
	std::array<int, 512> old = keys;

    glfwPollEvents();
    for (int i = 0; i < 512; i++) {
        keys[i] = glfwGetKey(window, i);
    }

    for (size_t i = 0; i < subscribers.size(); i++) {
        SunBase *subscriber = std::get<0>(subscribers[i]);
        int key = std::get<1>(subscribers[i]);
        int keyState = keys[key];
        int oldState = old[key];
        SunButtonEvent event = std::get<2>(subscribers[i]);

        SunAction action("key");
		action.addParameter("key", &key);

        switch (event) {
            case SunButtonEventUpSingle:
                if (keyState == GLFW_RELEASE && oldState == GLFW_PRESS) {
                    sendAction(action, subscriber);
                }
                break;
            case SunButtonEventDownSingle:
                if (keyState == GLFW_PRESS && oldState == GLFW_RELEASE) {
                    sendAction(action, subscriber);
                }
                break;
            case SunButtonEventUpContinuous:
                if (keyState == GLFW_RELEASE) {
                    sendAction(action, subscriber);
                }
                break;
            case SunButtonEventDownContinuous:
                if (keyState == GLFW_PRESS) {
                    sendAction(action, subscriber);
                }
                break;
        }
    }
}

void SunKeyboardManager::subscribe(SunBase *subscriber, int key, SunButtonEvent event) {
    std::tuple<SunBase *, int, SunButtonEvent> tuple = std::make_tuple(subscriber, key, event);
    subscribers.push_back(tuple);
}

SunButtonState SunKeyboardManager::pollKey(int key) {
    int state = glfwGetKey(window, key);
    if (state == GLFW_PRESS)
        return SunButtonStateDown;
    else if (state == GLFW_RELEASE)
        return SunButtonStateUp;
    return SunButtonStateNone;
}

bool SunKeyboardManager::keyDown(int key) {
    int state = glfwGetKey(window, key);
    if (state == GLFW_PRESS)
        return true;
    else if (state == GLFW_RELEASE)
        return false;
    return false;
}
