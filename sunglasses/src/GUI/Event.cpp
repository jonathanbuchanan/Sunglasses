#include <sunglasses/GUI/Event.h>

namespace sunglasses {
namespace GUI {

Event::Event(std::function<void()> &&_action) : action(_action) {

}

void Event::operator()() {
    action();
}

} // namespace
} // namespace
