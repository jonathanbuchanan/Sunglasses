// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNBASE_H
#define SUNBASE_H

#include <string>
#include <map>
#include <memory>

#include "SunAction.h"
#include "SunServiceManager.h"

/// An object with a name, a map of actions, and a map of services.
/**
 * SunBase is an abstract class that has a name, a map of actions, and a static map of
 * services. An action can be called by sending a SunAction to it with the appropriate
 * action name. The static list of services provides a way to access application-wide
 * services.
 */
class SunBase {
public:
    /// Default Constructor
    /**
     * This is the default constructor with no arguments. The name member (string)
     * is initialized empty, and the functions map member (map) is also empty.
     */
    SunBase();

    /// Constructor for the name member (string)
    /**
     * This constructor initializes the name member (string) with the single
     * parameter. The functions map is initialized empty.
     */
    SunBase(std::string n);

    /// Initializes the object.
    /**
     * This function should be called to initialize the object. Since SunBase shouldn't
     * ever be used on its own, this is a pure virtual member function which makes
     * SunBase abstract.
     */
    virtual void init() = 0;

    /// Adds an action for a name (string).
    /**
     * This function adds an action to the action map member (map) for an action
     * name (string). Since, all SunBase actions must have the same signature
     * (void(SunAction)), they are stored in the map as std::function.
     */
    template<typename Class>
    void addAction(std::string action, void (Class::*f)(SunAction)) {
        actions.emplace(action, std::bind(f, static_cast<Class *>(this), std::placeholders::_1));
    }

    /// Processes a SunAction.
    /**
     * This function processes an incoming SunAction. This function searches its
     * action list for the matching action, and executes it if it exists. If not,
     * it does nothing. This member function is virtual and therefore extensible,
     * and very useful when extended. This can be seen in SunNode, where the tags
     * feature is implemented.
     */
    virtual void processAction(SunAction action);

    /// Gets the name member (string).
    std::string getName() { return name; }

    /// Sets the name member (string).
    void setName(std::string n) { name = n; }

    /// A map containing services that correspond to names (strings)
    static SunServiceManager *services;
private:
    /// A string containing the name of the object
    std::string name;

    /// A map containing functions that correspond to names (strings)
    std::map<std::string, SunActionFunction> actions;
};

/// Sends a SunAction to a SunBase.
/**
 * This function automatically invokes processAction on the receiving object. Since
 * processAction is virtual, it will call a subclasses redefinition if it exists.
 */
extern void sendAction(SunAction action, SunBase *base);

#endif
