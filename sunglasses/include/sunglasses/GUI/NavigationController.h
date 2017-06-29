#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <stack>
#include <functional>

namespace sunglasses {
namespace GUI {

class Controller;
class GUIModule;

/// A class that allows for the manipulation of Controllers in the GUI
class NavigationController {
public:
    /// Constructs a navigation controller
    NavigationController(GUIModule &_system);


    /// Pushes a controller to the top and presents it
    void push(Controller *controller);

    /// Removes the top controller from view and presents the next
    void pop();

    /// Returns a reference to the controller at the top of the stack
    Controller * top();
private:
    /// The stack of controllers
    std::stack<Controller *> stack;

    /// A reference to the system
    GUIModule &system;
};

}
}

#endif
