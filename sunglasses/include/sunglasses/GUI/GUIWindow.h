// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GUIWINDOW_H
#define GUIWINDOW_H

#include <GL/glew.h>

#include <string>

#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

namespace sunglasses {

class GUIView;

enum struct GUIWindowButtonState {
    Released,
    Pressed
};

/// Input information for updating the GUI
struct GUIUpdateInfo {
    /// Constructs the update info
    GUIUpdateInfo(glm::ivec2 _cursor,
        GUIWindowButtonState _leftMouseButton,
        GUIWindowButtonState _rightMouseButton,
        GUIWindowButtonState _middleMouseButton);

    /// The position of the cursor
    glm::ivec2 cursor;

    /// The state of the left mouse button
    GUIWindowButtonState leftMouseButton;

    /// The state of the right mouse button
    GUIWindowButtonState rightMouseButton;

    /// The state of the middle mouse button
    GUIWindowButtonState middleMouseButton;
};

/// The window displaying the GUI
class GUIWindow {
public:
    /// The constructor, creating the window
    /**
     * This constructor initializes GLFW, creates the window,
     * sizes it, names it,
     */
    GUIWindow(int _width, int _height, std::string _title, bool resizeable = true);

    /// The destructor
    ~GUIWindow();

    /// Clears the window
    void clear();

    /// Swaps the window's buffers
    void swapBuffers();

    /// Returns the current update info
    GUIUpdateInfo updateInfo();

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
    GUIWindowButtonState leftMouseButton();

    /// Gets the state of the right mouse button
    GUIWindowButtonState rightMouseButton();

    /// Gets the state of the middle mouse button
    GUIWindowButtonState middleMouseButton();

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
