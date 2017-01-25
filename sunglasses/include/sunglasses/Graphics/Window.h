#ifndef __WINDOW_H
#define __WINDOW_H

#include <glm/glm.hpp>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <sunglasses/Core/Signal.h>

namespace sunglasses {
namespace graphics {

/// An object managing the window and the graphics context
class Window {
public:
    /// Creates a window and graphics context
    /**
     * Creates a window with the given size, title, and other options.
     * @param size The size of the window
     * @param title The title of the window
     */
    Window(glm::ivec2 size, std::string title);

    /// Destroys the window and graphics context
    ~Window();

    /// Sets the title of the window
    void setTitle(std::string title);


    /// Signal - Window close
    Signal<void()> signal_close;

    /// Signal - Window resize
    Signal<void(glm::ivec2)> signal_resize;

    /// Signal - Window move
    Signal<void(glm::ivec2)> signal_move;
private:
    /// Updates the viewport according to the size of the window
    void updateViewport();


    /// Called when the user tries to close the window
    static void windowClose(GLFWwindow *_window);

    /// Called when the user resizes the window
    static void windowResize(GLFWwindow *_window, int width, int height);

    /// Called when the user moves the window
    static void windowMove(GLFWwindow *_window, int x, int y);


    /// A pointer to the GLFW window object
    GLFWwindow *window;
};

}
}

#endif
