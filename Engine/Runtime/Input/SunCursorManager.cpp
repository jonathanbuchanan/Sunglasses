#include "SunCursorManager.h"

SunCursorManager::SunCursorManager() {
    
}

SunCursorManager::SunCursorManager(GLFWwindow *_window) {
    initialize(_window);
}

SunCursorManager::SunCursorManager(GLFWwindow *_window, bool disable) {
    initialize(_window, disable);
}

void SunCursorManager::initialize(GLFWwindow *_window) {
    window = _window;
}

void SunCursorManager::initialize(GLFWwindow *_window, bool disable) {
    window = _window;
    if (disable)
        disableCursor();
}

void SunCursorManager::update() {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    
    SunNodeSentAction action;
    action.action = "cursor";
    action.parameters["x"] = &x;
    action.parameters["y"] = &y;
    
    for (auto subscriber : subscribers)
        sendAction(action, subscriber);
}

void SunCursorManager::enableCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void SunCursorManager::disableCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

int SunCursorManager::getMode() {
    return glfwGetInputMode(window, GLFW_CURSOR);
}

glm::vec2 SunCursorManager::getCursorPosition() {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return glm::vec2(x, y);
}

void SunCursorManager::subscribe(SunNode *subscriber) {
    subscribers.push_back(subscriber);
}