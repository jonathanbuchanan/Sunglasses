#ifndef __WINDOW_H
#define __WINDOW_H

#include <glm/glm.hpp>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

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
private:
    /// Updates the viewport according to the size of the window
    void updateViewport();

    /// A pointer to the GLFW window object
    GLFWwindow *window;
};

}
}

#endif
