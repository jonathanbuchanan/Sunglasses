// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GUIMAINMENU_H
#define GUIMAINMENU_H

#include <sunglasses/Sunglasses.hpp>

using namespace sunglasses;
using namespace sunglasses::GUI;

class GUIMainMenu : public Controller {
public:
    GUIMainMenu(Window &window);
private:
    Panel v;
    Texture tex;
    Panel image;
    //Button button;
};

#endif
