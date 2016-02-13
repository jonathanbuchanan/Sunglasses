// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
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
    
	SunAction action("cursor");

    action.addParameter("x", &x);
	action.addParameter("y", &y); 
    
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

glm::vec2 SunCursorManager::getCursorPositionNDC() {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    
    return glm::vec2((x - (width / 2)) / (width / 2), (y - (height / 2)) / (height / 2));
}

void SunCursorManager::subscribe(SunBase *subscriber) {
    subscribers.push_back(subscriber);
}
