// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef OpenGL_Test_3_Scene_h
#define OpenGL_Test_3_Scene_h

#include "Core/SunBase.h"
#include "./Physics/SunPhysicsSimulator.h"
#include "./Graphics/SunTextRenderer.h"
#include "./GUI/SunGUISystem.h"
#include "./Graphics/SunCamera.h"
#include "./Graphics/SunRenderer.h"
#include "./Graphics/SunRenderingNode.h"
#include "./Graphics/SunPointShadowMapRenderingNode.h"
#include "./Graphics/SunTextRenderer.h"
#include "./Audio/SunSoundListener.h"
#include "./Audio/SunSoundBufferStorage.h"
#include "./Audio/SunMusicObject.h"
#include "./SunObject.h"
#include "./SunDirectionalLightObject.h"
#include "./SunPointLightObject.h"

// Definition of SunObjectType (NEEDS A HOME)

enum SunObjectType {
    SunObjectTypePhysical,
    SunObjectTypePointLight,
    SunObjectTypeDirectionalLight
};

typedef map<string, SunShader>::iterator SunShaderMapIterator;

class SunScene : public SunBase {
public:
    SunScene();
    SunScene(const char *filepath, GLFWwindow *_window);
    
    virtual void initializeDefaultPropertyAndFunctionMap();
    
    void initializeShadowMapRenderer(SunAction action);
    
    void cycle(map<int, SunButtonState> _buttons, GLfloat _deltaTime);
    virtual void update(map<int, SunButtonState> _buttons);
    virtual void render(SunAction action);
    void renderGUISystem(SunAction action);
    void passPerFrameUniforms(SunShader _shader);
    void passPerFrameUniforms(SunShader _shader, vector<SunNodeSentActionCondition> _conditions);
    virtual void passPerFrameUniformsAction(SunAction action);
    
    inline SunPhysicsSimulator & getPhysicsSimulator() { return physicsSimulator; }
    
    inline SunObject * getRootRenderableNode() { return rootRenderableNode; }
    
    inline SunCamera & getCamera() { return camera; }
    inline SunSoundListener & getListener() { return listener; }
    
    inline GLboolean & getDoCameraInput() { return doCameraInput; }
    inline void setDoCameraInput(GLboolean _x) { doCameraInput = _x; }
    
    inline int & getPointLightCount() { return pointLightCount; }
    inline void setPointLightCount(int _p) { pointLightCount = _p; }
    
    inline SunSoundBufferStorage & getSoundStorage() { return storage; }
    
    inline SunMusicObject * getMusic() { return music; }
    inline bool & getAutoplay() { return autoplay; }
    inline void setAutoplay(bool _autoplay) { autoplay = _autoplay; }
    
    inline GLFWwindow * getWindow() { return window; }
    inline void setWindow(GLFWwindow *_window) { window = _window; }
protected:
    // Root renderable node
    SunObject *rootRenderableNode;
    
    // Light Count
    int pointLightCount = 0;
    int shadowPointLightCount = 0;
    
    int directionalLightCount = 0;
    int shadowDirectionalLightCount = 0;
    
    // Camera
    SunCamera camera;
    SunSoundListener listener;
    GLboolean doCameraInput = true;
private:
    // Physics Simulator
    SunPhysicsSimulator physicsSimulator;

    // Renderer and Text Renderer
    SunRenderer renderer;
    
    
    // Shadow Point Light Pointers
    vector<SunPointLightObject *> shadowPointLights;
    
    // Sound Storage
    SunSoundBufferStorage storage;

    // Music
    SunMusicObject *music;
    bool autoplay;

    // Pointer to window
    GLFWwindow *window;
};

#endif
