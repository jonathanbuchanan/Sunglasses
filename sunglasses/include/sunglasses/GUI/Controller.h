// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <sunglasses/GUI/Panel.h>

namespace sunglasses {
namespace GUI {

class System;

/// Manages a view.
/**
 * This class manages an instance of View. This view typically
 * takes up the entire window.
 * @see View
 */
template<typename T>
class Controller {
friend System;
public:
    /// Constructs a view controller from the dimensions of the window
    Controller(System &system, const T &background) : panel(system, background) {
        system.addChild(panel);
    }

    /// The panel managed by the controller
    Panel<T> panel;
};

/// A 'basic' controller
using BasicController = Controller<Drawable::Color>;

} // namespace
} // namespace

#endif
