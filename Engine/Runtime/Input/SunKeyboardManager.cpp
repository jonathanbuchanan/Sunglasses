#include "SunKeyboardManager.h"

void SunKeyboardManager::initialize(GLFWwindow *window) {
	// Set the input mode to sticky keys
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
}
