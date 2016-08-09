// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>

#include <string>

#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

namespace sunglasses {

class View;

enum struct WindowButtonState {
    Released,
    Pressed
};

/// Input information for updating the GUI
struct UpdateInfo {
    /// Constructs the update info
    UpdateInfo(glm::ivec2 _cursor,
        WindowButtonState _leftMouseButton,
        WindowButtonState _rightMouseButton,
        WindowButtonState _middleMouseButton);

    /// The position of the cursor
    glm::ivec2 cursor;

    /// The state of the left mouse button
    WindowButtonState leftMouseButton;

    /// The state of the right mouse button
    WindowButtonState rightMouseButton;

    /// The state of the middle mouse button
    WindowButtonState middleMouseButton;
};

/// The window displaying the GUI
class Window {
public:
    /// The constructor, creating the window
    /**
     * This constructor initializes GLFW, creates the window,
     * sizes it, names it,
     */
    Window(int _width, int _height, std::string _title, bool resizeable = true);

    /// The destructor
    ~Window();

    /// Clears the window
    void clear();

    /// Swaps the window's buffers
    void swapBuffers();

    /// Returns the current update info
    UpdateInfo updateInfo();

    /// Returns the size of the window
    glm::ivec2 size();

    /// Updates the size of the viewport to match the framebuffer
    void updateViewport();

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
    WindowButtonState leftMouseButton();

    /// Gets the state of the right mouse button
    WindowButtonState rightMouseButton();

    /// Gets the state of the middle mouse button
    WindowButtonState middleMouseButton();

    /// The width of the window
    int width;

    /// The height of the window
    int height;

    /// The title of the window
    std::string title;

    /// The GLFW window
    GLFWwindow *window;
};

} // namespace

#endif
