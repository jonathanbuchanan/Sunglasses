// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNSCENE_H
#define SUNSCENE_H

#include "SunBase.h"
#include "../Physics/SunPhysicsSimulator.h"
#include "../Graphics/SunTextRenderer.h"
#include "../GUI/SunGUISystem.h"
#include "../GUI/SunGUIRenderer.h"
#include "../Graphics/SunCamera.h"
#include "../Graphics/SunTextRenderer.h"
#include "../Audio/SunSoundListener.h"
#include "../Audio/SunSoundBufferStorage.h"
#include "../Audio/SunMusicObject.h"
#include "SunObject.h"

class SunRenderer;

/// An abstract class that is responsible for game objects, rendering, etc.
/**
 * The SunScene class is a class that is responsible for maintaining the scene
 * graph, the rendering, audio, physics, game logic, and AI systems. The class
 * is abstract, so you must implement its initialization code yourself.
 */
class SunScene : public SunBase {
public:
    /// Default Constructor
    /**
     * The default constructor of SunScene initializes it with nothing.
     */
    SunScene();

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

    /// Gets the root member (SunObject pointer).
    SunObject * getRoot() { return root; }

    /// Sets the window member (GLFWwindow pointer).
    void setWindow(GLFWwindow *_window) { window = _window; }
protected:
    /// A pointer to the root object in the scene graph
    SunObject *root;

	/// A pointer to the scene renderer
	SunRenderer *renderer;
    /// A pointer to the GUI renderer
	SunGUIRenderer *guiRenderer;
    /// A pointer to the text renderer
	SunTextRenderer *textRenderer;

    /// The scene's camera
    SunCamera camera;
    /// OLD
    SunSoundListener listener;

    /// The physics simulator
    SunPhysicsSimulator physicsSimulator;

    /// OLD
    SunSoundBufferStorage storage;

    /// OLD
    SunMusicObject *music;
    /// OLD
    bool autoplay;

    /// A pointer to the window (GLFWwindow)
    GLFWwindow *window;
};

#endif
