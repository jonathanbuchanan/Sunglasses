#ifndef FeatureScene_H
#define FeatureScene_H

#include "SunScene.h"
#include "SunObject.h"

#include "FeatureRenderer.h"

class FeatureScene : public SunScene {
public:
    FeatureScene();
    
    void initialize();
    
    void cycle(float delta);
    
    inline void setWindow(GLFWwindow *w) { window = w; }

    inline void setServices(map<string, SunService *> *s) { services = s; }
private:
    void initializeDefaultPropertyAndFunctionMap();
    
    void render(SunNodeSentAction _action);
    
    // Services
    map<string, SunService *> *services;
    
    // GUI
    SunGUISystem guiSystem;
    
    SunObject *house;
    
    FeatureRenderer renderer;
    
    GLFWwindow *window;
};

#endif
