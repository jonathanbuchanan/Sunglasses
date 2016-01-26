#include "SunKeyboardManager.h"

SunKeyboardManager::SunKeyboardManager() {
    
}

void SunKeyboardManager::initialize(GLFWwindow *_window) {
    // Set the input mode to sticky keys
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, 1);
    window = _window;
}

void SunKeyboardManager::update() {
    glfwPollEvents();
    for (int i = 0; i < subscribers.size(); i++) {
        int state = glfwGetKey(window, subscribers[i].second);
        
        SunNodeSentAction action;
        action.parameters["key"] = &subscribers[i].second;
        if (state == GLFW_PRESS)
            action.action = "keyPress";
        else if (state == GLFW_RELEASE)
            action.action = "keyRelease";
        sendAction(action, subscribers[i].first);
    }
}

void SunKeyboardManager::subscribe(SunNode *subscriber, int key) {
    std::pair<SunNode *, int> pair = std::make_pair(subscriber, key);
    subscribers.push_back(pair);
}