// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <sunglasses/GUI/View.h>

namespace sunglasses {
namespace GUI {

class GUI;
class Window;

/// Manages a view.
/**
 * This class manages an instance of View. This view typically
 * takes up the entire window.
 * @see View
 */
class ViewController {
friend GUI;
public:
    /// Constructs a view controller from the dimensions of the window
    ViewController(Window &window, const Drawable &drawable = DrawableSolidColor(glm::vec4(1.0f)));
protected:
    /// The view managed by the controller
    View view;
};

} // namespace
} // namespace

#endif
