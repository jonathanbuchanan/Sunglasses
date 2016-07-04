// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNACTION_H
#define SUNACTION_H

#include <functional>
#include <string>
#include <map>

class SunBase;

typedef void * SunActionParameter;
typedef std::map<std::string, SunActionParameter> SunActionParameterMap;

/// An action which causes SunBase to perform an action when used on one.
/**
 * SunAction is a class that defines actions that can be sent to SunBase and its
 * derivatives. The action string determines which action will be picked from the
 * list of actions in a SunBase. It contains a map of parameters, which can be
 * used to pass along information, and a recursive boolean, which applies only to
 * SunNode, but it makes the node pass the action on to its subnodes.
 */
class SunAction {
public:
    /// Default Constructor
    /**
     * This is the default constructor with no arguments. The action string isn't
     * defined, the parameter map is empty, and recursive is set to false.
     */
    SunAction();

    /// Constructor for the action member (string)
    /**
     * This constructor initializes the action member (string) with the single parameter.
     * Recursive (boolean) is set to false.
     */
    SunAction(std::string a);

    /// Constructor for the action member (string) and parameter map (map)
    /**
     * This constructor initializes the action member (string) and the parameter
     * map member. Recursive (boolean) is set to false.
     */
    SunAction(std::string a, SunActionParameterMap p);

    /// Constructor for the action member (string), parameter map (map), and recursive member (boolean)
    /**
     * This constructor initializes the action member (string), the parameter map
     * member (map), and the recursive member (boolean).
     */
    SunAction(std::string a, SunActionParameterMap p, bool r);

    /// Sets the action member (string).
    void setAction(std::string a) { action = a; }
    /// Gets the action member (string).
    std::string getAction() { return action; }

    /// Checks to see if the parameter map contains the specified parameter name.
    bool parameterExists(std::string p) { return parameters.find(p) != parameters.end(); }

    /// Gets a parameter from the parameter map.
    /**
     * Since the parameter map is a map that has strings for keys and void pointers
     * as values so it can store any size type, each pointer needs to be casted.
     * This function takes a template parameter and a string that is the name of
     * the parameter. This functions gets the value for the key, casts it to a
     * pointer of the specified type, dereferences it, and returns it.
     */
    template<typename T>
    T getParameter(std::string parameter) {
        return *(T *)parameters[parameter];
    }

    /// Gets a parameter from the parameter map in pointer form.
    /**
     * Since the parameter map is a map that has strings for keys and void pointers
     * as values so it can store any size type, each pointer needs to be casted.
     * This function takes a template parameter and a string that is the name of
     * the parameter. This functions gets the value for the key, casts it to a
     * pointer of the specified type, and returns it.
     */
    template<typename T>
    T * getParameterPointer(std::string parameter) {
        return (T *)parameters[parameter];
    }

    /// Gets a parameter from the parameter map.
    /**
     * This function returns a void pointer from the map for the specified key.
     */
    void * getParameter(std::string p) { return parameters[p]; }

    /// Adds a parameter to the map
    /**
     * This function adds a parameter to the map (in the form of a void pointer)
     * with the specified key.
     */
    void addParameter(std::string k, void *v) { parameters[k] = v; }

    /// Gets the recursive member (boolean).
    bool getRecursive() { return recursive; }
    /// Sets the recursive member (boolean).
    void setRecursive(bool r) { recursive = r; }
private:
    /// A string containing the name of the action to be performed
    std::string action;

    /// A map of parameters
    SunActionParameterMap parameters;

    /// A boolean that determines whether this action should be recursive when performed on SunNode
    bool recursive = false;
};

typedef std::function<void(SunAction)> SunActionFunction;

#endif
