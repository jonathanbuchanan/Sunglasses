// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GUIMAINMENU_H
#define GUIMAINMENU_H

#include <sunglasses/Sunglasses.hpp>

class GUIMainMenu : public SunGUIViewController {
public:
    GUIMainMenu(SunGUIWindow &window);
private:
    SunGUIView v;
    SunGUIButton button;
};

#endif
