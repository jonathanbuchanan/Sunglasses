#ifndef EVENT_H
#define EVENT_H

#include <functional>

namespace sunglasses {

namespace GUI {

/// A class that defines a callable action by GUI elements
/**
 * For example, an event may be triggered by a window's
 * close button being pressed, or a butten getting highlighted.
 */
class Event {
public:
    /// Initializes it with a function temporary
    Event(std::function<void()> &&_action);

    /// Initializes it with a type that can be converted to a function
    template<typename T>
    Event(T object) : action(object) {

    }

    /// Calls the event
    void operator()();
private:
    /// The function called when the event is triggered
    std::function<void()> action;
};

} // namespace
} // namespace

#endif
