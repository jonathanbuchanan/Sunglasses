//
//  SunGUIMenu.h
//  Sunglasses
//
//  Created by Jonathan Buchanan on 6/12/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef Sunglasses_SunGUIMenu_h
#define Sunglasses_SunGUIMenu_h

#include <vector>

#include "./SunGUIItem.h"

class SunGUIMenu : public SunNode {
public:
    
    SunGUIMenu() {
        initializeDefaultPropertyAndFunctionMap();
    }
    
    void hide(SunNodeSentAction _action);
    void show(SunNodeSentAction _action);
    void toggleMouse(SunNodeSentAction _action);
    void closeWindow(SunNodeSentAction _action);
    void initializeDefaultPropertyAndFunctionMap();
    map<string, GLboolean> activeTriggers(map<int, SunButtonState> _buttons);
    void sendActions(map<string, GLboolean> _activeTriggers);
    void update(SunNodeSentAction _action);
    void render(SunNodeSentAction _action);
    
    inline GLboolean getVisible() { return visible; }
    inline void setVisible(GLboolean _visible) { visible = _visible; }
    
    inline vector<SunNodeSentAction> & getSentActions() { return sentActions; }
    inline SunNodeSentAction * getSentActionAtIndex(int i) { return &sentActions[i]; }
    inline void addSentAction(SunNodeSentAction action) { sentActions.push_back(action); }
    
    inline GLFWwindow * getWindow() { return window; }
    inline void setWindow(GLFWwindow *_window) { window = _window; }
private:
    GLboolean visible;
    
    vector<SunNodeSentAction> sentActions;
    
    GLFWwindow *window;
};

#endif
