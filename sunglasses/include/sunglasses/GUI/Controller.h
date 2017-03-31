// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <sunglasses/GUI/GUIModule.h>
#include <sunglasses/GUI/Panel.h>
#include <sunglasses/Graphics/GraphicsModule.h>

namespace sunglasses {
namespace graphics {

class Window;

}

namespace GUI {

class NavigationController;

/// The interface for a controller
class IController {
friend NavigationController;
public:
    /// Presents the controller on the system
    virtual void present() = 0;

    /// Performs any necessary actions when this controller is not being viewed
    virtual void close() = 0;
protected:
    /// A pointer to the navigation controller currently using the controller
    NavigationController *navigationController = nullptr;
};

/// Manages a view.
/**
 * This class manages an instance of View. This view typically
 * takes up the entire window.
 * @see View
 */
template<typename T>
class Controller : public IController {
friend GUIModule;
public:
    /// Constructs a view controller from the dimensions of the window
    Controller(GUIModule &_system, const T &background) :
        panel(_system.getGraphicsModule().window, background), system(_system) {

    }

    /// Presents the controller on the system
    virtual void present() {
        system.present(panel);
    }

    /// Performs any necessary actions when this controller is not being viewed
    virtual void close() {
        panel.closeAll();
    }

    /// The panel managed by the controller
    Panel<T> panel;
protected:
    /// A reference to the system that contains it
    GUIModule &system;
};

/// A 'basic' controller
using BasicController = Controller<Drawable::Color>;

} // namespace
} // namespace

#endif
