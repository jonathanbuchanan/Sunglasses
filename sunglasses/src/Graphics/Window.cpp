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


    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Size the viewport correctly
    updateViewport();
}

Window::~Window() {
    glfwTerminate();
}

void Window::updateViewport() {
    glm::ivec2 size;
    glfwGetFramebufferSize(window, &size.x, &size.y);

    glViewport(0, 0, size.x, size.y);
}

}
}
