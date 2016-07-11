// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/SunGUI.h>

#include <sunglasses/GUI/SunGUIView.h>
#include <sunglasses/GUI/SunGUIViewController.h>

SunGUI::SunGUI(SunGUIView *view, SunGUIWindow &_window) :
    window(_window), contentView(view) {

}

SunGUI::SunGUI(SunGUIViewController &viewController, SunGUIWindow &_window) :
    window(_window), contentView(&viewController.view) {

}
