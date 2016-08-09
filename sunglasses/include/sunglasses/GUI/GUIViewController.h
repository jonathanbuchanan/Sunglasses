// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GUIVIEWCONTROLLER_H
#define GUIVIEWCONTROLLER_H

#include <sunglasses/GUI/GUIView.h>

namespace sunglasses {

class GUI;
class GUIWindow;

/// Manages a view.
/**
 * This class manages an instance of GUIView. This view typically
 * takes up the entire window.
 * @see GUIView
 */
class GUIViewController {
friend GUI;
public:
    /// Constructs a view controller from the dimensions of the window
    GUIViewController(GUIWindow &window, const GUIDrawable &drawable = GUIDrawableSolidColor(glm::vec4(1.0f)));
protected:
    /// The view managed by the controller
    GUIView view;
};

} // namespace

#endif
