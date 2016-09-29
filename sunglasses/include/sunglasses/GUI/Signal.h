#ifndef SIGNAL_H
#define SIGNAL_H

#include <set>
#include <functional>

namespace sunglasses {
namespace GUI {

template<typename T>
class ISlot;

template<typename T>
class Signal;

/// A class representing a signal (event)
template<typename R, typename... T>
class Signal<R(T...)> {
public:
    Signal & operator=(const Signal &) = delete;

    /// Emits the signal
    /**
     * Emits the signal by activating all the associated slots.
     */
    void emit(T &&... args) {
        for (auto slot : slots)
            slot->activate(std::forward<T>(args)...);
    }

    /// Emits the signal
    void operator()(T &&... args) {
        emit(std::forward<T>(args)...);
    }

    /// Adds a slot to the set of slots
    void addSlot(const ISlot<R(T...)> *slot) {
        slots.insert(slot);
    }

    /// Removes a slot from the set of slots
    void removeSlot(const ISlot<R(T...)> *slot) {
        slots.erase(slot);
    }
private:
    /// The set of slots that the signal is connected to
    std::set<const ISlot<R(T...)> *> slots;
};

/// The interface for the slot class
template<typename R, typename... T>
class ISlot<R(T...)> {
public:
    /// Removes all connections to signals
    /*virtual ~ISlot() {
        for (auto &signal : signals)
            signal->removeSlot(this);
    }*/

    /// Activates the slot
    virtual void activate(T &&... args) const = 0;

    /// Activates the slot
    virtual void operator()(T &&... args) const = 0;

    /// Adds a signal to the set of signals
    void addSignal(const Signal<R(T...)> *signal) {
        signals.insert(signal);
    }

    /// Removes a signal from the set of signals
    void removeSignal(const Signal<R(T...)> *signal) {
        signals.erase(signal);
    }
protected:
    /// The set of signals
    std::set<const Signal<R(T...)> *> signals;
};

template<typename T, T function>
class Slot {

};

/// A class representing a slot (something that can receive an event)
template<typename T, typename R, typename... A, R(T::*function)(A...)>
class Slot<R(T::*)(A...), function> : public ISlot<R(A...)> {
public:
    /// Constructs the slot with a reference
    Slot(T &_object) : object(_object) {

    }

    Slot & operator=(const Slot &) = delete;

    /// Activates the slot
    virtual void activate(A &&... args) const {
        (object.*function)(std::forward<A>(args)...);
    }

    /// Activates the slot
    virtual void operator()(A &&... args) const {
        activate(std::forward<A>(args)...);
    }
private:
    /// A reference to the object that the slot will notify
    T &object;
};

/// Connects a signal to a slot
template<typename R, typename... A>
void connect(Signal<R(A...)> &signal, ISlot<R(A...)> &slot) {
    signal.addSlot(&slot);
    slot.addSignal(&signal);
}

/// Disconnects a signal and a slot
template<typename... T>
void disconnect(Signal<T...> &signal, ISlot<T...> &slot) {
    signal.removeSlot(&slot);
    slot.removeSignal(&signal);
}

} // namespace
} // namespace

#endif
