// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef FeatureScene_H
#define FeatureScene_H

#include "SunScene.h"
#include "SunObject.h"

#include "FeatureRenderer.h"

class FeatureScene : public SunScene {
public:
    FeatureScene();
    
    void init();
    
    void cycle(float delta);
    
    inline void setWindow(GLFWwindow *w) { window = w; }

    inline void setServices(map<string, SunService *> *s) { services = s; }
private: 
    void renderGUI(SunAction action);
    
    // Services
    map<string, SunService *> *services;
    
    // GUI
    SunGUISystem guiSystem = SunGUISystem();
    SunGUIMenu *menu;
    SunGUIItem *item;
    
    SunObject *house;
    
    // Render
    FeatureRenderer renderer;
    SunTextRenderer textRenderer;
    
    GLFWwindow *window;
};

#endif
