#include <sunglasses/Graphics/Window.h>

namespace sunglasses {
namespace graphics {

Window::Window(glm::ivec2 size, std::string title) {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the user pointer and callbacks
    glfwSetWindowUserPointer(window, this);

    glfwSetWindowCloseCallback(window, Window::windowClose);
    glfwSetWindowSizeCallback(window, Window::windowResize);
    glfwSetWindowPosCallback(window, Window::windowMove);


    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Size the viewport correctly
    updateViewport();
}

Window::~Window() {
    glfwTerminate();
}

void Window::setTitle(std::string title) {
    glfwSetWindowTitle(window, title.c_str());
}

void Window::updateViewport() {
    glm::ivec2 size;
    glfwGetFramebufferSize(window, &size.x, &size.y);

    glViewport(0, 0, size.x, size.y);
}


void Window::windowClose(GLFWwindow *_window) {
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(_window));
    window->signal_close.emit();
}

void Window::windowResize(GLFWwindow *_window, int width, int height) {
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(_window));
    window->signal_resize.emit(glm::ivec2(width, height));
}

void Window::windowMove(GLFWwindow *_window, int x, int y) {
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(_window));
    window->signal_move.emit(glm::ivec2(x, y));
}

}
}
