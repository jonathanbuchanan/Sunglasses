// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/WindowManager.h>
#include <sunglasses/Scripting/Script.h>

namespace sunglasses {

template<> const std::map<std::string, Scripting::LuaTypeDataMemberBase<WindowManager> *> LuaTypeRegistrar<WindowManager>::dataMembers = {
    {"setWindowShouldClose", new LuaTypeMemberFunction<WindowManager, void>("setWindowShouldClose", &WindowManager::setWindowShouldClose)}
};

WindowManager::WindowManager() {

}

WindowManager::WindowManager(glm::vec2 _size, std::string _title, glm::vec4 _clearColor) {
    size = _size;
    title = _title;
    clearColor = _clearColor;
    initialize();
}

void WindowManager::update() {

}

void WindowManager::initialize() {
    // Initialize GLFW and give window hints
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (window == NULL) {
        //std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        //std::cout << "Failed to initialize GLEW" << std::endl;
    }

    glViewport(0, 0, size.x, size.y);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable hardware gamma correction
    glEnable(GL_FRAMEBUFFER_SRGB);

    // Set blending function
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set the clear color
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

void WindowManager::terminate() {
    glfwTerminate();
}

void WindowManager::swapBuffers() {
    glfwSwapBuffers(window);
}

void WindowManager::setWindowShouldClose() {
    glfwSetWindowShouldClose(window, true);
}

void WindowManager::calculateDelta() {
    double currentFrame = glfwGetTime();
    delta = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

} // namespace
