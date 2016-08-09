// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Input/KeyboardManager.h>
#include <sunglasses/Scripting/Script.h>

namespace sunglasses {

template<> const std::string LuaTypeRegistrar<KeyboardManager>::typeName = "KeyboardManager";
template<> const std::map<std::string, Scripting::LuaTypeDataMemberBase<KeyboardManager> *> LuaTypeRegistrar<KeyboardManager>::dataMembers = {
    {"pollKey", new LuaTypeMemberFunction<KeyboardManager, bool, int>("pollKey", &KeyboardManager::keyDown)}
};

KeyboardManager::KeyboardManager() {

}

KeyboardManager::KeyboardManager(GLFWwindow *_window) {
    initialize(_window);
}

void KeyboardManager::initialize(GLFWwindow *_window) {
    // Set the input mode to sticky keys
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, 1);
    window = _window;
}

void KeyboardManager::update() {
    std::array<int, 512> old = keys;

    glfwPollEvents();
    for (int i = 0; i < 512; i++) {
        keys[i] = glfwGetKey(window, i);
    }

    for (size_t i = 0; i < subscribers.size(); i++) {
        Base *subscriber = std::get<0>(subscribers[i]);
        int key = std::get<1>(subscribers[i]);
        int keyState = keys[key];
        int oldState = old[key];
        ButtonEvent event = std::get<2>(subscribers[i]);

        Action action("key");
        action.addParameter("key", &key);

        switch (event) {
            case ButtonEventUpSingle:
                if (keyState == GLFW_RELEASE && oldState == GLFW_PRESS) {
                    sendAction(action, subscriber);
                }
                break;
            case ButtonEventDownSingle:
                if (keyState == GLFW_PRESS && oldState == GLFW_RELEASE) {
                    sendAction(action, subscriber);
                }
                break;
            case ButtonEventUpContinuous:
                if (keyState == GLFW_RELEASE) {
                    sendAction(action, subscriber);
                }
                break;
            case ButtonEventDownContinuous:
                if (keyState == GLFW_PRESS) {
                    sendAction(action, subscriber);
                }
                break;
        }
    }
}

void KeyboardManager::registerWithScript(Script *script) {
    script->registerType<KeyboardManager>();
    script->registerObject(this, "keyboard_manager");
}

void KeyboardManager::subscribe(Base *subscriber, int key, ButtonEvent event) {
    std::tuple<Base *, int, ButtonEvent> tuple = std::make_tuple(subscriber, key, event);
    subscribers.push_back(tuple);
}

ButtonState KeyboardManager::pollKey(int key) {
    int state = glfwGetKey(window, key);
    if (state == GLFW_PRESS)
        return ButtonStateDown;
    else if (state == GLFW_RELEASE)
        return ButtonStateUp;
    return ButtonStateNone;
}

bool KeyboardManager::keyDown(int key) {
    int state = glfwGetKey(window, key);
    if (state == GLFW_PRESS)
        return true;
    else if (state == GLFW_RELEASE)
        return false;
    return false;
}

} // namespace
