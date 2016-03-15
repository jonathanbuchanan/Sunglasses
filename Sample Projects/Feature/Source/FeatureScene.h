// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef FeatureScene_H
#define FeatureScene_H

#include <Sunglasses/Sunglasses.hpp>

#include "FeatureRenderer.h"

class FeatureScene : public SunScene {
public:
    FeatureScene();

    void init();
    void cycle();

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
    std::vector<SunObject *> teapots;

    GLFWwindow *window;
};

#endif
