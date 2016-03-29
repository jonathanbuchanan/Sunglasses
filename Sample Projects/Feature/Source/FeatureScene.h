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
    std::shared_ptr<SunGUIMenu> menu;
    std::shared_ptr<SunGUIItem> item;
    std::shared_ptr<SunGUIItem> back;

    // Objects
    std::shared_ptr<SunObject> plane;
    SunPointLight *light;
    std::shared_ptr<SunDirectionalLight> dir;
    std::vector<std::shared_ptr<SunObject>> teapots;
    std::shared_ptr<SunCamera> camera;

    GLFWwindow *window;
};

#endif
