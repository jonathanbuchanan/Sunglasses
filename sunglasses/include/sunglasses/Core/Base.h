// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef BASE_H
#define BASE_H

#include <string>
#include <map>
#include <memory>

#include <sunglasses/Core/Action.h>
#include <sunglasses/Core/ServiceManager.h>

namespace sunglasses {

/// An object with a name, a map of actions, and a map of services.
/**
 * Base is an abstract class that has a name, a map of actions, and a static map of
 * services. An action can be called by sending a Action to it with the appropriate
 * action name. The static list of services provides a way to access application-wide
 * services.
 */
class Base {
public:
    /// Default Constructor
    /**
     * This is the default constructor with no arguments. The name member (string)
     * is initialized empty, and the functions map member (map) is also empty.
     */
    Base();

    /// Constructor for the name member (string)
    /**
     * This constructor initializes the name member (string) with the single
     * parameter. The functions map is initialized empty.
     */
    Base(std::string n);

    /// Initializes the object.
    /**
     * This function should be called to initialize the object. Since Base shouldn't
     * ever be used on its own, this is a pure virtual member function which makes
     * Base abstract.
     */
    virtual void init() = 0;

    /// Adds an action for a name (string).
    /**
     * This function adds an action to the action map member (map) for an action
     * name (string). Since, all Base actions must have the same signature
     * (void(Action)), they are stored in the map as std::function.
     */
    template<typename Class>
    void addAction(std::string action, void (Class::*f)(Action)) {
        actions.emplace(action, std::bind(f, static_cast<Class *>(this), std::placeholders::_1));
    }

    /// Processes a Action.
    /**
     * This function processes an incoming Action. This function searches its
     * action list for the matching action, and executes it if it exists. If not,
     * it does nothing. This member function is virtual and therefore extensible,
     * and very useful when extended. This can be seen in Node, where the tags
     * feature is implemented.
     */
    virtual void processAction(Action action);

    /// Gets the name member (string).
    std::string getName() { return name; }

    /// Sets the name member (string).
    void setName(std::string n) { name = n; }

    /// A map containing services that correspond to names (strings)
    static ServiceManager services;
private:
    /// A string containing the name of the object
    std::string name;

    /// A map containing functions that correspond to names (strings)
    std::map<std::string, ActionFunction> actions;
};

/// Sends a Action to a Base.
/**
 * This function automatically invokes processAction on the receiving object. Since
 * processAction is virtual, it will call a subclasses redefinition if it exists.
 */
extern void sendAction(Action action, Base *base);

} // namespace

#endif
