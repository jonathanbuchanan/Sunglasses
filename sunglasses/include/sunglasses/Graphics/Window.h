#ifndef __WINDOW_H
#define __WINDOW_H

#include <glm/glm.hpp>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <sunglasses/Core/Signal.h>
#include <sunglasses/Graphics/Framebuffer.h>

namespace sunglasses {
namespace graphics {

/// An object managing the window and the graphics context
class Window {
private:
	/// An object representing the framebuffer controlled by the window
    class WindowFramebuffer: public IFramebuffer {
    public:
    	/// Constructs the framebuffer with a reference to the window
    	WindowFramebuffer(Window &_window) : window(_window) { }

		/// Activates (binds) the framebuffer
		virtual void activate() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		/// Clears the framebuffer
		virtual void clear(glm::vec4 color) {
			glClearColor(color.r, color.g, color.b, color.a);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		/// Returns the size of the framebuffer
		virtual glm::ivec2 getSize() {
			return window.getSize();
		}
    private:
    	/// The reference to the window
    	Window &window;
    };
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

    /// Sets the viewport of the window
    void setViewport(glm::ivec2 origin, glm::ivec2 size);

    /// Sizes the viewport of the window to the size of the window
    void sizeViewportToWindow();

    /// Gets the size of the window
    glm::ivec2 getSize() const;

    /// Clears the window
    void clear(glm::vec4 = glm::vec4(1.0f));

    /// Swaps the buffers of the window
    void swapBuffers();

    /// Updates the window by polling for events
    void update();


    /// Signal - Window close
    Signal<void()> signal_close;

    /// Signal - Window resize
    Signal<void(glm::ivec2)> signal_resize;

    /// Signal - Window move
    Signal<void(glm::ivec2)> signal_move;


    /// An object representing the cursor
    class Cursor {
        friend Window;
    public:
        /// Signal - Cursor move
        Signal<void(glm::ivec2)> signal_move;

        /// Signal - Press left button
        Signal<void(glm::ivec2)> signal_pressLeft;

        /// Signal - Release left button
        Signal<void(glm::ivec2)> signal_releaseLeft;

        /// Signal - Press middle button
        Signal<void(glm::ivec2)> signal_pressMiddle;

        /// Signal - Release middle button
        Signal<void(glm::ivec2)> signal_releaseMiddle;

        /// Signal - Press right button
        Signal<void(glm::ivec2)> signal_pressRight;

        /// Signal - Release right button
        Signal<void(glm::ivec2)> signal_releaseRight;

        /// Signal - Scroll
        Signal<void(glm::vec2)> signal_scroll;
    private:
        /// Called when the user moves the cursor
        static void cursorMove(GLFWwindow *_window, double x, double y);

        /// Called when the user presses/releases a mouse button
        static void mouseButton(GLFWwindow *_window, int button, int action, int mods);

        /// Called when the user scrolls the mouse
        static void mouseScroll(GLFWwindow *_window, double xOffset, double yOffset);
    } cursor;

    /// An object representing the keyboard
    class Keyboard {
        friend Window;
    public:
        /// Signal - Key press
        Signal<void(int)> signal_press;

        /// Signal - Key repeat
        Signal<void(int)> signal_repeat;

        /// Signal - Key release
        Signal<void(int)> signal_release;
    private:
        /// Called when the user presses/repeats/releases a key
        static void key(GLFWwindow *_window, int key, int scancode, int action, int mods);
    } keyboard;
    
    WindowFramebuffer framebuffer;
private:
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
