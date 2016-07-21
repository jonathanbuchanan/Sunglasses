// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIWINDOW_H
#define SUNGUIWINDOW_H

#include <GL/glew.h>

#include <string>

#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

class SunGUIView;

enum struct SunGUIWindowButtonState {
    Released,
    Pressed
};

/// Input information for updating the GUI
struct SunGUIUpdateInfo {
    /// Constructs the update info
    SunGUIUpdateInfo(glm::ivec2 _cursor,
        SunGUIWindowButtonState _leftMouseButton,
        SunGUIWindowButtonState _rightMouseButton,
        SunGUIWindowButtonState _middleMouseButton);

    /// The position of the cursor
    glm::ivec2 cursor;

    /// The state of the left mouse button
    SunGUIWindowButtonState leftMouseButton;

    /// The state of the right mouse button
    SunGUIWindowButtonState rightMouseButton;

    /// The state of the middle mouse button
    SunGUIWindowButtonState middleMouseButton;
};

/// The window displaying the GUI
class SunGUIWindow {
public:
    /// The constructor, creating the window
    /**
     * This constructor initializes GLFW, creates the window,
     * sizes it, names it,
     */
    SunGUIWindow(int _width, int _height, std::string _title);

    /// The destructor
    ~SunGUIWindow();

    /// Clears the window
    void clear();

    /// Swaps the window's buffers
    void swapBuffers();
    
    /// Returns the current update info
    SunGUIUpdateInfo updateInfo();
    /// Returns the size of the window
    glm::ivec2 size() { return glm::ivec2(width, height); }

    /// Creates a projection matrix
    /**
     * The projection matrix converts points in pixel-space to points in
     * normalized device coordinate space. The origin is in the bottom left
     * corner.
     */
    glm::mat4 projection();
private:
    /// Gets the cursor position in integer coordinates
    glm::ivec2 cursor();

    /// Gets the state of the left mouse button
    SunGUIWindowButtonState leftMouseButton();

    /// Gets the state of the right mouse button
    SunGUIWindowButtonState rightMouseButton();

    /// Gets the state of the middle mouse button
    SunGUIWindowButtonState middleMouseButton();

    /// The width of the window
    int width;

    /// The height of the window
    int height;

    /// The title of the window
    std::string title;

    /// The GLFW window
    GLFWwindow *window;
};

#endif
