#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <stack>
#include <functional>

namespace sunglasses {
namespace GUI {

class IController;
class System;

/// A class that allows for the manipulation of Controllers in the GUI
class NavigationController {
public:
    /// Constructs a navigation controller
    NavigationController(System &_system);


    /// Pushes a controller to the top and presents it
    void push(IController &controller);

    /// Removes the top controller from view and presents the next
    void pop();

    /// Returns a reference to the controller at the top of the stack
    IController & top();
private:
    /// The stack of controllers
    std::stack<std::reference_wrapper<IController>> stack;

    /// A reference to the system
    System &system;
};

}
}

#endif
