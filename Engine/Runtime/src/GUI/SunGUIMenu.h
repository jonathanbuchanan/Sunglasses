// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef Sunglasses_SunGUIMenu_h
#define Sunglasses_SunGUIMenu_h

#include <map>

#include "SunGUIItem.h"
#include "../Input/SunCursorManager.h"
#include "../Scripting/SunScript.h"

class SunGUIMenu : public SunNode {
public:

    SunGUIMenu();

    virtual void init();

    void loadScript(std::string _script);

    void render(SunAction action);

    void key(SunAction action);

    inline void setCursorManager(SunCursorManager *c) { cursor = c; }
    inline SunCursorManager * getCursorManager() { return cursor; }

    inline bool & getVisible() { return visible; }
    inline void setVisible(bool v) { visible = v; }

    SunScript * getScript() { return &script; }
private:
    SunCursorManager *cursor;

    bool visible = false;

    SunScript script;
};

#endif
