// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Input/CursorManager.h>
#include <sunglasses/Scripting/Script.h>

namespace sunglasses {

template<> const std::string LuaTypeRegistrar<CursorManager>::typeName = "CursorManager";
template<> const std::map<std::string, Scripting::LuaTypeDataMemberBase<CursorManager> *> LuaTypeRegistrar<CursorManager>::dataMembers = {
    {"enableCursor", new LuaTypeMemberFunction<CursorManager, void>("enableCursor", &CursorManager::enableCursor)},
    {"disableCursor", new LuaTypeMemberFunction<CursorManager, void>("disableCursor", &CursorManager::disableCursor)}
};

CursorManager::CursorManager() {

}

CursorManager::CursorManager(GLFWwindow *_window) {
    initialize(_window);
}

CursorManager::CursorManager(GLFWwindow *_window, bool disable) {
    initialize(_window, disable);
}

void CursorManager::initialize(GLFWwindow *_window) {
    window = _window;
}

void CursorManager::initialize(GLFWwindow *_window, bool disable) {
    window = _window;
    if (disable)
        disableCursor();
}

void CursorManager::update() {
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    Action action("cursor");

    action.addParameter("x", &x);
    action.addParameter("y", &y);

    for (auto subscriber : subscribers)
        sendAction(action, subscriber);
}

void CursorManager::enableCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void CursorManager::disableCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

int CursorManager::getMode() {
    return glfwGetInputMode(window, GLFW_CURSOR);
}

glm::vec2 CursorManager::getCursorPosition() {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return glm::vec2(x, y);
}

glm::vec2 CursorManager::getCursorPositionNDC() {
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    return glm::vec2((x - (width / 2)) / (width / 2), (y - (height / 2)) / (height / 2));
}

void CursorManager::subscribe(Base *subscriber) {
    subscribers.push_back(subscriber);
}

} // namespace
