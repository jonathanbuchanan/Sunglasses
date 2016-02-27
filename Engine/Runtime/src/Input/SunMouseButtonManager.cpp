// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunMouseButtonManager.h"

SunMouseButtonManager::SunMouseButtonManager() {
    
}

SunMouseButtonManager::SunMouseButtonManager(GLFWwindow *_window) {
    initialize(_window);
}

void SunMouseButtonManager::initialize(GLFWwindow *_window) {
    // Set the input mode to sticky
    window = _window;
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
}

void SunMouseButtonManager::update() {
    std::array<int, 8> old = buttons;
    
    glfwPollEvents();
    for (int i = 0; i < 7; i++) {
        buttons[i] = glfwGetMouseButton(window, i);
    }
    
    for (int i = 0; i < subscribers.size(); i++) {
        SunBase *subscriber = std::get<0>(subscribers[i]);
        int button = std::get<1>(subscribers[i]);
        int buttonState = buttons[button];
        int oldState = old[button];
        SunButtonEvent event = std::get<2>(subscribers[i]);
        
		SunAction action("button");
		action.addParameter("button", &button);

        switch (event) {
            case SunButtonEventUpSingle:
                if (buttonState == GLFW_RELEASE && oldState == GLFW_PRESS) { 
                    sendAction(action, subscriber);
                }
                break;
            case SunButtonEventDownSingle:
                if (buttonState == GLFW_PRESS && oldState == GLFW_RELEASE) { 
                    sendAction(action, subscriber);
                }
                break;
            case SunButtonEventUpContinuous:
                if (buttonState == GLFW_RELEASE) { 
                    sendAction(action, subscriber);
                }
                break;
            case SunButtonEventDownContinuous:
                if (buttonState == GLFW_PRESS) { 
                    sendAction(action, subscriber);
                }
                break;
        }
    }
}

void SunMouseButtonManager::subscribe(SunBase *subscriber, int button, SunButtonEvent event) {
    std::tuple<SunBase *, int, SunButtonEvent> tuple = std::make_tuple(subscriber, button, event);
    subscribers.push_back(tuple);
}

SunButtonState SunMouseButtonManager::pollButton(int button) {
    int state = glfwGetMouseButton(window, button);
    if (state == GLFW_PRESS)
        return SunButtonStateDown;
    else if (state == GLFW_RELEASE)
        return SunButtonStateUp;
}
