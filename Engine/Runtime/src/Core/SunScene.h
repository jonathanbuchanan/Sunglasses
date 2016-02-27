// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef OpenGL_Test_3_Scene_h
#define OpenGL_Test_3_Scene_h

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

class SunScene : public SunBase {
public:
    SunScene();

    virtual void init();

	template<typename T>
	void initRenderer() {
		renderer = new T();
	}

	virtual void cycle();

    inline SunPhysicsSimulator & getPhysicsSimulator() { return physicsSimulator; }

    inline SunObject * getRoot() { return root; }

    inline SunCamera & getCamera() { return camera; }
    inline SunSoundListener & getListener() { return listener; }

    inline GLboolean & getDoCameraInput() { return doCameraInput; }
    inline void setDoCameraInput(GLboolean _x) { doCameraInput = _x; }

    inline SunSoundBufferStorage & getSoundStorage() { return storage; }

    inline SunMusicObject * getMusic() { return music; }
    inline bool & getAutoplay() { return autoplay; }
    inline void setAutoplay(bool _autoplay) { autoplay = _autoplay; }

    inline GLFWwindow * getWindow() { return window; }
    inline void setWindow(GLFWwindow *_window) { window = _window; }
protected:
    // Root
    SunObject *root;

	// Renderers
	SunRenderer *renderer;
	SunGUIRenderer *guiRenderer;
	SunTextRenderer *textRenderer;

    // Camera
    SunCamera camera;
    SunSoundListener listener;
    GLboolean doCameraInput = true;
private:
    // Physics Simulator
    SunPhysicsSimulator physicsSimulator;

    // Sound Storage
    SunSoundBufferStorage storage;

    // Music
    SunMusicObject *music;
    bool autoplay;

    // Pointer to window
    GLFWwindow *window;
};

#endif
