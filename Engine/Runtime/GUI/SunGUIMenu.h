// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef Sunglasses_SunGUIMenu_h
#define Sunglasses_SunGUIMenu_h

#include <map>

#include "GUI/SunGUIAction.h"
#include "GUI/SunGUIItem.h"
#include "Input/SunCursorManager.h"

class SunGUIMenu : public SunNode {
public:
    
    SunGUIMenu();
    
    void initializeDefaultPropertyAndFunctionMap();
    
    void render(SunNodeSentAction _action);
    
    void key(SunNodeSentAction _action);
    
    inline void setCursorManager(SunCursorManager *c) { cursor = c; }
    inline SunCursorManager * getCursorManager() { return cursor; }
    
    inline bool & getVisible() { return visible; }
    inline void setVisible(bool v) { visible = v; }
    
    inline void addActionForKey(SunGUIAction a, int k) { actions[k] = a; }
private:
    SunCursorManager *cursor;
    
    bool visible = false;
    
    std::map<int, SunGUIAction> actions;
};

#endif