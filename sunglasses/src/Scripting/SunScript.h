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

#include <sunglasses/Scripting/SunLuaValue.h>
#include <sunglasses/Scripting/SunLuaCFunction.h>
#include <sunglasses/Scripting/SunLuaTypeRegistrar.h>

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

    /// Closes the Lua state
    void close();

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

    /// Registers a C++ type
    /**
     * @see SunLuaTypeRegistrar
     */
    template<typename T>
    void registerType() {
        SunLuaTypeRegistrar<T>::registerInState(state);
    }

    /// Registers a set of C++ types
    /**
     * @see SunLuaTypeRegistrar
     */
    template<typename T, typename S, typename... R>
    void registerTypes() {
        registerType<T>();
        registerTypes<S, R...>();
    }

    /// Registers a set of C++ types
    /**
     * @see SunLuaTypeRegistrar
     */
    template<typename T>
    void registerTypes() {
        registerType<T>();
    }

    /// Registers a C++ object
    /**
     * @see SunLuaTypeRegistrar
     */
    template<typename T>
    void registerObject(T *object, std::string name) {
        SunLuaTypeRegistrar<T>::registerObject(state, object);
        lua_setglobal(state, name.c_str());
    }

    /// Adds an object.
    //void _addObject(std::shared_ptr<_SunPrivateScripting::_SunLuaObject_Base> object);
private:
    /// The Lua state.
    lua_State *state;
    /// The vector of C functions.
    std::vector<_SunPrivateScripting::_SunLuaCFunction_Base *> functions;
    /// The map of registered objects.
    //std::vector<std::shared_ptr<_SunPrivateScripting::_SunLuaObject_Base>> objects;
    /// The map of registered types.
    //std::map<std::string, std::shared_ptr<_SunPrivateScripting::_SunLuaType_Base>> types;
};

#endif
