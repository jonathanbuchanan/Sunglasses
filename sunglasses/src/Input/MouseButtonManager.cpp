// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Input/MouseButtonManager.h>
#include <sunglasses/Scripting/Script.h>

namespace sunglasses {

template<> const std::string LuaTypeRegistrar<MouseButtonManager>::typeName = "MouseButtonManager";
template<> const std::map<std::string, Scripting::LuaTypeDataMemberBase<MouseButtonManager> *> LuaTypeRegistrar<MouseButtonManager>::dataMembers = {
    //{"pollKey", new LuaTypeMemberFunction<KeyboardManager, bool, int>("pollKey", &KeyboardManager::keyDown)}
};

MouseButtonManager::MouseButtonManager() {

}

MouseButtonManager::MouseButtonManager(GLFWwindow *_window) {
    initialize(_window);
}

void MouseButtonManager::initialize(GLFWwindow *_window) {
    // Set the input mode to sticky
    window = _window;
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
}

void MouseButtonManager::update() {
    std::array<int, 8> old = buttons;

    glfwPollEvents();
    for (int i = 0; i < 7; i++) {
        buttons[i] = glfwGetMouseButton(window, i);
    }

    for (size_t i = 0; i < subscribers.size(); i++) {
        Base *subscriber = std::get<0>(subscribers[i]);
        int button = std::get<1>(subscribers[i]);
        int buttonState = buttons[button];
        int oldState = old[button];
        ButtonEvent event = std::get<2>(subscribers[i]);

        Action action("button");
        action.addParameter("button", &button);

        switch (event) {
            case ButtonEventUpSingle:
                if (buttonState == GLFW_RELEASE && oldState == GLFW_PRESS) {
                    sendAction(action, subscriber);
                }
                break;
            case ButtonEventDownSingle:
                if (buttonState == GLFW_PRESS && oldState == GLFW_RELEASE) {
                    sendAction(action, subscriber);
                }
                break;
            case ButtonEventUpContinuous:
                if (buttonState == GLFW_RELEASE) {
                    sendAction(action, subscriber);
                }
                break;
            case ButtonEventDownContinuous:
                if (buttonState == GLFW_PRESS) {
                    sendAction(action, subscriber);
                }
                break;
        }
    }
}

void MouseButtonManager::subscribe(Base *subscriber, int button, ButtonEvent event) {
    std::tuple<Base *, int, ButtonEvent> tuple = std::make_tuple(subscriber, button, event);
    subscribers.push_back(tuple);
}

ButtonState MouseButtonManager::pollButton(int button) {
    int state = glfwGetMouseButton(window, button);
    if (state == GLFW_PRESS)
        return ButtonStateDown;
    else if (state == GLFW_RELEASE)
        return ButtonStateUp;
    return ButtonStateNone;
}

} // namespace
