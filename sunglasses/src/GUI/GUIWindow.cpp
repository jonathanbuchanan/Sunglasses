// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/SunGUIWindow.h>

#include <glm/gtc/matrix_transform.hpp>

namespace sunglasses {

SunGUIUpdateInfo::SunGUIUpdateInfo(glm::ivec2 _cursor,
    SunGUIWindowButtonState _leftMouseButton,
    SunGUIWindowButtonState _rightMouseButton,
    SunGUIWindowButtonState _middleMouseButton) : cursor(_cursor),
        leftMouseButton(_leftMouseButton), rightMouseButton(_rightMouseButton),
        middleMouseButton(_middleMouseButton) { }

SunGUIWindow::SunGUIWindow(int _width, int _height, std::string _title, bool resizeable)
    : width(_width), height(_height), title(_title) {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizeable);

    // Create the window
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        // TODO: ERROR!
    }
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);



    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        // TODO: ERROR!
    }
    
    // Update the viewport
    updateViewport();
}

SunGUIWindow::~SunGUIWindow() {
    glfwTerminate();
}

void SunGUIWindow::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void SunGUIWindow::swapBuffers() {
    glfwSwapBuffers(window);
}

SunGUIUpdateInfo SunGUIWindow::updateInfo() {
    glfwPollEvents();
    return SunGUIUpdateInfo(
        cursor(),
        leftMouseButton(),
        rightMouseButton(),
        middleMouseButton()
    );
}

glm::ivec2 SunGUIWindow::size() {
    glm::ivec2 size;
    glfwGetWindowSize(window, &size.x, &size.y);
    return size;
}

void SunGUIWindow::updateViewport() {
    // Set the viewport
    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

    glViewport(0, 0, framebufferWidth, framebufferHeight);
}

glm::mat4 SunGUIWindow::projection() {
    glm::ivec2 windowSize = size();
    return glm::ortho(0.0f, (float)windowSize.x, (float)windowSize.y, 0.0f, -1.0f, 0.0f);
}

glm::ivec2 SunGUIWindow::cursor() {
    glm::dvec2 cursor;
    glfwGetCursorPos(window, &cursor.x, &cursor.y);
    return (glm::ivec2)cursor;
}

SunGUIWindowButtonState SunGUIWindow::leftMouseButton() {
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
        return SunGUIWindowButtonState::Pressed;
    else if (state == GLFW_RELEASE)
        return SunGUIWindowButtonState::Released;
}

SunGUIWindowButtonState SunGUIWindow::rightMouseButton() {
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if (state == GLFW_PRESS)
        return SunGUIWindowButtonState::Pressed;
    else if (state == GLFW_RELEASE)
        return SunGUIWindowButtonState::Released;
}

SunGUIWindowButtonState SunGUIWindow::middleMouseButton() {
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
    if (state == GLFW_PRESS)
        return SunGUIWindowButtonState::Pressed;
    else if (state == GLFW_RELEASE)
        return SunGUIWindowButtonState::Released;
}

} // namespace
