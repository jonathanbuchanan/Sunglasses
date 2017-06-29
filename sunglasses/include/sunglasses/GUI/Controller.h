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

/// Manages a panel
class Controller {
friend GUIModule;
friend NavigationController;
public:
    /// Constructs a view controller from the dimensions of the window
    Controller(GUIModule &_system) :
        panel(_system.getGraphicsModule().window), system(_system) {

    }

    /// Presents the controller on the system
    virtual void present() {
        system.present(panel);
    }

    /// Performs any necessary actions when this controller is not being viewed
    virtual void close() {
        //panel.closeAll();
    }

    /// The panel managed by the controller
    Panel panel;
protected:
    /// A reference to the system that contains it
    GUIModule &system;
    
    /// A pointer to the navigation controller currently using the controller
    NavigationController *navigationController = nullptr;
};

} // namespace
} // namespace

#endif
