// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGUIWindow.h"

SunGUIWindow::SunGUIWindow(int _width, int _height, std::string _title)
    : width(_width), height(_height), title(_title) {
    // Initialize GLFW
    if (!glfwInit()) {
        // TODO: ERROR!
    }

    // Create the window
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        // TODO: ERROR!
    }
    glfwMakeContextCurrent(window);
}

SunGUIWindow::~SunGUIWindow() {
    glfwTerminate();
}
