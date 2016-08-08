// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIVIEWCONTROLLER_H
#define SUNGUIVIEWCONTROLLER_H

#include <sunglasses/GUI/SunGUIView.h>

class SunGUI;
class SunGUIWindow;

/// Manages a view.
/**
 * This class manages an instance of SunGUIView. This view typically
 * takes up the entire window.
 * @see SunGUIView
 */
class SunGUIViewController {
friend SunGUI;
public:
    /// Constructs a view controller from the dimensions of the window
    SunGUIViewController(SunGUIWindow &window, const SunGUIDrawable &drawable = SunGUIDrawableSolidColor(glm::vec4(1.0f)));
protected:
    /// The view managed by the controller
    SunGUIView view;
};

#endif
