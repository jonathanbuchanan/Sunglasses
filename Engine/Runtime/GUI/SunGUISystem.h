// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef Sunglasses_SunGUISystem_h
#define Sunglasses_SunGUISystem_h

#include <vector>
#include <string>

#include "Utility.h"

#include "./SunGUIMenu.h"
#include "./SunGUIItem.h"

using namespace std;

struct SunGUIFont {
    string file;
    string name;
};

class SunGUISystem : public SunNode {
public:
    SunGUISystem() { initializeDefaultPropertyAndFunctionMap(); }
    
    virtual void initializeDefaultPropertyAndFunctionMap();
    virtual void render(SunAction action);
    void loadFonts(SunTextRenderer *_textRenderer);
    
    inline vector<SunGUIFont> & getFonts() { return fonts; }
    inline SunGUIFont & getFontAtIndex(int i) { return fonts[i]; }
    inline void addFont(SunGUIFont font) { fonts.push_back(font); }
    
    inline bool & getFontsLoaded() { return fontsLoaded; }
    inline void setFontsLoaded(bool _fontsLoaded) { fontsLoaded = _fontsLoaded; }
private:
    vector<SunGUIFont> fonts;
    bool fontsLoaded = false;
};

#endif
