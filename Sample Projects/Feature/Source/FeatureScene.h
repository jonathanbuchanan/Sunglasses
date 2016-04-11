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

    std::weak_ptr<SunGUIMenu> menu;
    std::weak_ptr<SunGUIItem> item;
    std::weak_ptr<SunGUIItem> back;

    // Objects
    std::weak_ptr<SunObject> plane;
    std::weak_ptr<SunShadowDirectionalLight> dir;
    std::weak_ptr<SunShadowPointLight> pt;
    std::vector<std::weak_ptr<SunObject>> teapots;
    std::weak_ptr<SunCamera> camera;

    GLFWwindow *window;
};

#endif
