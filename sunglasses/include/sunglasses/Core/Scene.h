// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SCENE_H
#define SCENE_H

#include "Base.h"
#include "../Physics/PhysicsSimulator.h"
#include "../Graphics/Camera.h"
#include "Object.h"

namespace sunglasses {

class Renderer;

/// An abstract class that is responsible for game objects, rendering, etc.
/**
 * The Scene class is a class that is responsible for maintaining the scene
 * graph, the rendering, audio, physics, game logic, and AI systems. The class
 * is abstract, so you must implement its initialization code yourself.
 */
class Scene : public Base {
public:
    /// Default Constructor
    /**
     * The default constructor of Scene initializes it with nothing.
     */
    Scene();

    /// Initializes the object.
    /**
     * This pure virtual member function is where the code that sets up the scene
     * graph and initializes the "cycle objects (renderer, physics simulator, etc.)".
     */
    virtual void init() = 0;

    /// Performs the actions required every game loop.
    /**
     * This function does the things required every cycle to make the game run.
     * These things include sending the update action to the scene graph, rendering
     * the scene, simulating physics, etc. You must override this to provide your own
     * functionality every cycle in your scene.
     */
    virtual void cycle();

    /// Gets the root member (Object pointer).
    Node * getRoot() { return root.get(); }

    /// Sets the window member (GLFWwindow pointer).
    void setWindow(GLFWwindow *_window) { window = _window; }
protected:
    /// A pointer to the root object in the scene graph
    std::unique_ptr<Node> root;

    /// A pointer to the scene renderer
    Renderer *renderer;

    /// The physics simulator
    PhysicsSimulator physicsSimulator;

    /// A pointer to the window (GLFWwindow)
    GLFWwindow *window;
};

} // namespace

#endif
