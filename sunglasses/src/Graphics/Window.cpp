#include <sunglasses/Graphics/Window.h>

namespace sunglasses {
namespace graphics {

Window::Window(glm::ivec2 size, std::string title) : framebuffer(*this) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    if (window == nullptr)
    	throw std::runtime_error("could not create window");
    glfwMakeContextCurrent(window);

    // Set the user pointer and callbacks
    glfwSetWindowUserPointer(window, this);

    glfwSetWindowCloseCallback(window, Window::windowClose);
    glfwSetWindowSizeCallback(window, Window::windowResize);
    glfwSetWindowPosCallback(window, Window::windowMove);
    glfwSetCursorPosCallback(window, Window::Cursor::cursorMove);
    glfwSetMouseButtonCallback(window, Window::Cursor::mouseButton);
    glfwSetScrollCallback(window, Window::Cursor::mouseScroll);
    glfwSetKeyCallback(window, Window::Keyboard::key);


    glfwSwapInterval(1);


    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    	throw std::runtime_error("could not load OpenGL functions");

    // Size the viewport correctly
    sizeViewportToWindow();
}

Window::~Window() {
    glfwTerminate();
}

void Window::setTitle(std::string title) {
    glfwSetWindowTitle(window, title.c_str());
}

void Window::setViewport(glm::ivec2 origin, glm::ivec2 size) {
    glViewport(origin.x, origin.y, size.x, size.y);
}

void Window::sizeViewportToWindow() {
    glm::ivec2 size;
    glfwGetFramebufferSize(window, &size.x, &size.y);

    setViewport(glm::ivec2(0), size);
}

glm::ivec2 Window::getSize() const {
    glm::ivec2 size;
    glfwGetFramebufferSize(window, &size.x, &size.y);

    return size;
}

void Window::clear(glm::vec4 color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::update() {
    glfwPollEvents();
}



void Window::Cursor::cursorMove(GLFWwindow *_window, double x, double y) {
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(_window));
    window->cursor.signal_move.emit(glm::vec2(x, y));
}

void Window::Cursor::mouseButton(GLFWwindow *_window, int button, int action, int mods) {
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(_window));
    glm::dvec2 position;
    glfwGetCursorPos(_window, &position.x, &position.y);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        window->cursor.signal_pressLeft.emit(position);
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        window->cursor.signal_releaseLeft.emit(position);
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
        window->cursor.signal_pressMiddle.emit(position);
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
        window->cursor.signal_releaseMiddle.emit(position);
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        window->cursor.signal_pressRight.emit(position);
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        window->cursor.signal_releaseRight.emit(position);
}

void Window::Cursor::mouseScroll(GLFWwindow *_window, double xOffset, double yOffset) {
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(_window));
    window->cursor.signal_scroll.emit(glm::vec2(xOffset, yOffset));
}

void Window::Keyboard::key(GLFWwindow *_window, int key, int scancode, int action, int mods) {
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(_window));
    if (action == GLFW_PRESS)
        window->keyboard.signal_press.emit(key);
    else if (action == GLFW_REPEAT)
        window->keyboard.signal_repeat.emit(key);
    else if (action == GLFW_RELEASE)
        window->keyboard.signal_repeat.emit(key);
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
