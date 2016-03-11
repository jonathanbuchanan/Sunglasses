// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGAME_H
#define SUNGAME_H

#include <iostream>
#include <unistd.h>
#include <string>
#include <map>

#include "SunBase.h"

#include "SunScene.h"
#include "../Graphics/SunWindowManager.h"
#include "../Input/SunKeyboardManager.h"
#include "../Input/SunCursorManager.h"
#include "../Input/SunMouseButtonManager.h"
#include "../Output/SunLogger.h"

class SunScene;

/// An abstract class which controls the scene
/**
 * The SunGame abstract class defines an object that contains the scene. At startup, it
 * instantiates all of the services. It also runs the large loop that controls
 * the game. During this loop it sends an update signal to each service. It also
 * quits when it finds glfwWindowShouldClose is true.
 */
class SunGame : public SunBase {
public:
    /// This is the default constructor which does nothing
    SunGame();

    /// Contains the game loop
    /**
     * This function contains the game loop. Once run, it doesn't stop until
     * glfwWindowShouldClose is set to true. Upon the loop ending, it terminates
     * the window. Inside the loop, it calls the pure virtual function loop().
     * This is where user defined functionality should go.
     */
	void run();

    /// Pure virtual function exectued every game cycle
    /**
     * This function is called by the game loop every time that it runs. Since it
     * is a pure virtual function, the functionality must be defined by the user
     * in a subclass.
     */
	virtual void loop() = 0;

    /// Updates the registered services.
    /**
     * This function is called by the game loop every time that it runs. It iterates
     * through the map of services and updates each one.
     */
    void updateServices();

    /// Cleans up the game after termination
    /**
     * This function should be called by main() after the run function is over.
     * It cleans up all of the memory that relates to the game and then closes
     * the application.
     */
    void cleanUp();

    /// Initializes the services (window manager, cursor manager, keyboard manager, mouse button manager, and logger).
    /**
     * Initializes the services (window manager, cursor manager, keyboard manager,
     * mouse button manager, and logger). By default, this creates a window with
     * no title and a clear color of (0, 0, 0, 0).
     */
    void init();

    /// Initializes the services (window manager, cursor manager, keyboard manager, mouse button manager, and logger) with the parameters.
    /**
     * Initializes the services (window manager, cursor manager, keyboard manager,
     * mouse button manager, and logger). The first parameter (string) determines
     * the title of the window, and the second parameter (vec4) determines the
     * clear color of the window.
     */
	void init(std::string title, glm::vec4 color);
protected:
    /// A pointer to the scene, which contains the scene graph
	SunScene *scene;

    /// A pointer to the GLFW window
    GLFWwindow *window;
};

#endif
