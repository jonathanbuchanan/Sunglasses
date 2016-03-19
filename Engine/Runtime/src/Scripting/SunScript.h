// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNSCRIPT_H
#define SUNSCRIPT_H

#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <lua.hpp>

#include "SunLuaValue.h"
#include "SunLuaState.h"
#include "SunLuaCFunction.h"
#include "SunLuaObject.h"
#include "SunLuaType.h"

/// A container for a lua script that interacts with the engine
/**
 * SunScript is the engine's way of using a Lua script to interact with the it.
 * You can load files, retrieve variables, create variables, run Lua code, register
 * C functions, C++ classes, and C++ types.
 */
class SunScript {
public:
    SunScript();
    ~SunScript();

    /// Loads a Lua file.
    /**
     * This function loads a Lua file upon being called. Specifically, it runs
     * luaL_dofile, which loads the file into the state and runs it.
     */
    void loadFile(std::string file);

    /// Gets a global variable for a name (string).
    /**
     * This function retrieves a _SunPrivateScripting::SunLuaValue based on the supplied
     * key (string). The return type can be casted to primitive types, and it can be
     * used to access its members if it is a table.
     */
    _SunPrivateScripting::SunLuaValue getVariable(std::string var);

    /// Gets a global variable for a name (string).
    /**
     * This function retrieves a _SunPrivateScripting::SunLuaValue based on the supplied
     * key (string). The return type can be casted to primitive types, and it can be
     * used to access its members if it is a table.
     */
    _SunPrivateScripting::SunLuaValue operator[](std::string var);

    /// Runs a piece of Lua code.
    /**
     * This function takes a string of Lua code and runs it. This function does
     * not return anything, even when running a function that has a return.
     */
    void run(std::string code);

    /// Runs a piece of Lua code.
    /**
     * This function takes a string of Lua code and runs it. This function does
     * not return anything, even when running a function that has a return.
     */
    void operator()(std::string code);

    /// Registers an std::function.
    /**
     * This function registers an std::function for a given name in the script.
     * The arguments and return types are expected to be castable to Lua primitives.
     * This function can be called from Lua. Remember, function overloading is not
     * supported.
     */
    template<typename S, typename... T>
    void registerFunction(std::string name, std::function<S(T...)> _function) {
        functions.push_back(new _SunPrivateScripting::SunLuaCFunction<S, T...>(state, name, _function));
    }

    /// Registers a C function pointer.
    /**
     * This function registers a C function pointer for a given name in the script.
     * The arguments and return types are expected to be castable to Lua primitives.
     * This function can be called from Lua. Remember, function overloading is not
     * supported.
     */
    template<typename S, typename... T>
    void registerFunction(std::string name, S (* _function)(T...)) {
        functions.push_back(new _SunPrivateScripting::SunLuaCFunction<S, T...>(state, name, std::function<S(T...)>(_function)));
    }

    /// Registers an std::function.
    /**
     * This function registers an std::function for a given value in the script.
     * This value can be a global value or a table member.
     * The arguments and return types are expected to be castable to Lua primitives.
     * This function can be called from Lua. Remember, function overloading is not
     * supported.
     */
    template<typename S, typename... T>
    void registerFunction(_SunPrivateScripting::SunLuaValue value, std::function<S(T...)> _function) {
        functions.push_back(new _SunPrivateScripting::SunLuaCFunction<S, T...>(state, value, _function));
    }

    /// Registers a C function pointer.
    /**
     * This function registers a C function pointer for a given value in the script.
     * This value can be a global value or a table member.
     * The arguments and return types are expected to be castable to Lua primitives.
     * This function can be called from Lua. Remember, function overloading is not
     * supported.
     */
    template<typename S, typename... T>
    void registerFunction(_SunPrivateScripting::SunLuaValue value, S (* _function)(T...)) {
        functions.push_back(new _SunPrivateScripting::SunLuaCFunction<S, T...>(state, value, std::function<S(T...)>(_function)));
    }

    /// Registers a C++ object.
    /**
     * This function registers a C++ object. This first parameter should be the name
     * of the object (string), the second should be a pointer to it, and then
     * the remain parameters register the member functions, alternating between
     * function names (first) and function pointers (second).
     */
    template<typename S, typename... T>
    void registerObject(std::string name, S *object, T... functions) {
        objects.push_back(std::unique_ptr<_SunPrivateScripting::_SunLuaObject_Base>(new _SunPrivateScripting::SunLuaObject<S, T...>(state, name.c_str(), object, functions...)));
    }

    /// Registers a C++ object.
    /**
     * This function registers a C++ object. This first parameter should be a _SunPrivateScripting::SunLuaValue
     * pointing to where the object should be stored, the second should be a pointer to it, and then
     * the remain parameters register the member functions, alternating between
     * function names (first) and function pointers (second).
     */
    template<typename S, typename... T>
    void registerObject(_SunPrivateScripting::SunLuaValue value, S *object, T... functions) {
        objects.push_back(std::unique_ptr<_SunPrivateScripting::_SunLuaObject_Base>(new _SunPrivateScripting::SunLuaObject<S, T...>(state, value, object, functions...)));
    }

    /// Registers a C++ type.
    /**
     * This function is similar to registering an object, except it doesn't take a
     * pointer to an object. This makes it easier to register multiple objects of the
     * same type, because you can just use the type instead of manually listing members.
     */
    template<typename S, typename... T>
    void registerType(std::string type, T... members) {
        types[type] = std::shared_ptr<_SunPrivateScripting::_SunLuaType_Base>(new _SunPrivateScripting::SunLuaType<S, T...>(members...));
    }

    /// Registers a C++ object as a stored type.
    /**
     * This function takes a name for the object (string), the type to be registered
     * under (string), and a pointer to the object to be registered.
     */
    template<typename T>
    void registerObjectAsType(std::string name, std::string type, T *object) {
        auto element = types[type];
        element->registerObject(state, name.c_str(), object);
    }

    /// Registers a C++ object as a stored type.
    /**
     * This function takes a _SunPrivateScripting::SunLuaValue for the location of the object, the type to be registered
     * under (string), and a pointer to the object to be registered.
     */
    template<typename T>
    void registerObjectAsType(_SunPrivateScripting::SunLuaValue value, std::string type, T *object) {
        auto element = types[type];
        element->registerObject(state, value, object);
    }

    /// Prints the size of the Lua stack.
    void printTop() {
        std::cout << std::to_string(state->getTop());
    }

    /// Adds an object.
    void _addObject(std::shared_ptr<_SunPrivateScripting::_SunLuaObject_Base> object);
private:
    /// The Lua state.
    _SunPrivateScripting::SunLuaState *state;
    /// The vector of C functions.
    std::vector<_SunPrivateScripting::_SunLuaCFunction_Base *> functions;
    /// The map of registered objects.
    std::vector<std::shared_ptr<_SunPrivateScripting::_SunLuaObject_Base>> objects;
    /// The map of registered types.
    std::map<std::string, std::shared_ptr<_SunPrivateScripting::_SunLuaType_Base>> types;
};

#endif
