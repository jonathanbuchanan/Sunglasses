#include <sunglasses/GUI/NavigationController.h>

#include <sunglasses/GUI/Controller.h>

namespace sunglasses {
namespace GUI {

NavigationController::NavigationController(System &_system) :
        system(_system) {

}

void NavigationController::push(IController &controller) {
    /// Close the current top controller
    if (!stack.empty())
        top().close();

    /// Push the next controller
    stack.push(controller);

    controller.navigationController = this;

    top().present();
}

void NavigationController::pop() {
    /// Close the top controller
    top().close();
    top().navigationController = nullptr;

    /// Pop the stack
    stack.pop();

    if (!stack.empty())
        top().present();
}

IController & NavigationController::top() {
    return stack.top();
}

}
}
