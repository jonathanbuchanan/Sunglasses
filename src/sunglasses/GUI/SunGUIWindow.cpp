// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/SunGUIWindow.h>

#include <glm/gtc/matrix_transform.hpp>

SunGUIWindow::SunGUIWindow(int _width, int _height, std::string _title)
    : width(_width), height(_height), title(_title) {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create the window
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        // TODO: ERROR!
    }
    glfwMakeContextCurrent(window);



    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        // TODO: ERROR!
    }

    // Set the viewport
    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

    glViewport(0, 0, framebufferWidth, framebufferHeight);
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

glm::ivec2 SunGUIWindow::cursorPosition() {
    glm::dvec2 position;
    glfwGetCursorPos(window, &position.x, &position.y);

    return glm::ivec2(position);
}

glm::mat4 SunGUIWindow::projection() {
    return glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 0.0f);
}
