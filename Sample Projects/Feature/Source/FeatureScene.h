// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef FeatureScene_H
#define FeatureScene_H

#include "SunScene.h"
#include "SunObject.h"

#include "Extra/SunPointLight.h"
#include "Extra/SunDirectionalLight.h"

#include "FeatureRenderer.h"
#include "GUI/SunGUIRenderer.h"

class FeatureScene : public SunScene {
public:
    FeatureScene();
    
    void init(); 
    
    inline void setWindow(GLFWwindow *w) { window = w; } 
private: 
	// GUI
    SunGUISystem guiSystem = SunGUISystem();
    SunGUIMenu *menu;
    SunGUIItem *item;

	// Objects
    SunObject *house;
	SunObject *plane;
	SunPointLight *light;
	SunDirectionalLight *dir;
    
    GLFWwindow *window;
};

#endif
