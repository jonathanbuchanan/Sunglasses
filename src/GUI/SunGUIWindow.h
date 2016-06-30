// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIWINDOW_H
#define SUNGUIWINDOW_H

#include <string>

#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

class SunGUIView;

/// The window displaying the GUI
class SunGUIWindow {
public:
    /// The constructor, creating the window
    /**
     * This constructor initializes GLFW, creates the window,
     * sizes it, names it, 
     */
    SunGUIWindow(int _width, int _height, std::string _title, SunGUIView *view = nullptr);

    /// The destructor
    ~SunGUIWindow();

    /// Draws the window
    /**
     * This method draws the content view. It also is
     * responsible for configuring all of the drawing.
     */
    void draw();
private:
    /// The width of the window
    int width;

    /// The height of the window
    int height;

    /// The title of the window
    std::string title;

    /// The GLFW window
    GLFWwindow *window;

    /// A pointer to the content view
    SunGUIView *contentView;
};

#endif
