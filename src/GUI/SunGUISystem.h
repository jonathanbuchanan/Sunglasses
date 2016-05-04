// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef SUNGUISYSTEM_H
#define SUNGUISYSTEM_H

#include <vector>
#include <string>

#include "SunGUIMenu.h"
#include "SunGUIItem.h"

struct SunGUIFont {
    std::string file;
    std::string name;
};

class SunGUISystem : public SunNode {
public:
    SunGUISystem() { }

    virtual void init();
    virtual void render(SunAction action);
    void loadFonts(SunTextRenderer *_textRenderer);

    inline std::vector<SunGUIFont> & getFonts() { return fonts; }
    inline SunGUIFont & getFontAtIndex(int i) { return fonts[i]; }
    inline void addFont(SunGUIFont font) { fonts.push_back(font); }

    inline bool & getFontsLoaded() { return fontsLoaded; }
    inline void setFontsLoaded(bool _fontsLoaded) { fontsLoaded = _fontsLoaded; }
private:
    std::vector<SunGUIFont> fonts;
    bool fontsLoaded = false;
};

#endif
