// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNWINDOWMANAGER_H
#define SUNWINDOWMANAGER_H

#include <sunglasses/Core/SunBase.h>
#include <sunglasses/Core/SunService.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

class SunWindowManager : public SunService {
public:
    SunWindowManager();
    SunWindowManager(glm::vec2 _size, std::string _title, glm::vec4 _clearColor);

    void update();

    void initialize();
    void terminate();

    void swapBuffers();
    void setWindowShouldClose();

    void calculateDelta();

    GLFWwindow * getWindow() { return window; }

    glm::vec2 getSize() { return size; }
    void setSize(glm::vec2 s) { size = s; }

    std::string getTitle() { return title; }
    void setTitle(std::string t) { title = t; }

    void setClearColor(glm::vec4 c) { clearColor = c; }

    double getDelta() { return delta; }
private:
    GLFWwindow *window;

    glm::vec2 size;
    std::string title;

    glm::vec4 clearColor;

    double lastFrame;
    double delta;
};

#endif
