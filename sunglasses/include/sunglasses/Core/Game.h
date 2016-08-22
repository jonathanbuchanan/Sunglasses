// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <unistd.h>
#include <string>
#include <map>
#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Base.h"
#include "../Input/CLOptionParsing.h"

namespace sunglasses {

class Scene;

/// An abstract class which controls the scene
/**
 * The Game abstract class defines an object that contains the scene. At startup, it
 * instantiates all of the services. It also runs the large loop that controls
 * the game. During this loop it sends an update signal to each service. It also
 * quits when it finds glfwWindowShouldClose is true.
 */
class Game {
public:
    /// This is the default constructor
    Game(int argc, char **argv, std::string title);

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


    /// Stops the game
    void stop();
protected:
    /// A pointer to the scene, which contains the scene graph
    Scene *scene;

private:
    /// A boolean that controls the stopping of the game
    bool endGame = false;

    // TODO: Use better design!
};

} // namespace

#endif
