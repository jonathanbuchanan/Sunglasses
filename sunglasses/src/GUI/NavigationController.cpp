#include <sunglasses/GUI/NavigationController.h>

#include <sunglasses/GUI/Controller.h>

namespace sunglasses {
namespace GUI {

NavigationController::NavigationController(System &_system) : system(_system) {

}

void NavigationController::push(IController &controller) {
    stack.push(controller);

    controller.navigationController = this;

    ((IController &)stack.top()).present(system);
}

void NavigationController::pop() {
    top().navigationController = nullptr;

    stack.pop();

    ((IController &)stack.top()).present(system);
}

IController & NavigationController::top() {
    return stack.top();
}

}
}
