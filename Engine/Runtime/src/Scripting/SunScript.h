// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNSCRIPT_H
#define SUNSCRIPT_H

#include <map>
#include <memory>
#include <iostream>
#include <lua.hpp>

#include "SunLuaValue.h"
#include "SunLuaState.h"
#include "SunLuaCFunction.h"
#include "SunLuaObject.h"

class SunScript {
public:
    SunScript();
    ~SunScript();

    void loadFile(std::string file);

    _SunPrivateScripting::SunLuaValue getVariable(std::string var);
    _SunPrivateScripting::SunLuaValue operator[](std::string var);

    void run(std::string code);
    void operator()(std::string code);

    template<typename S, typename... T>
    void registerFunction(std::string name, std::function<S(T...)> _function) {
        functions.push_back(new _SunPrivateScripting::SunLuaCFunction<S, T...>(state, name, _function));
    }

    template<typename S, typename... T>
    void registerFunction(std::string name, S (* _function)(T...)) {
        functions.push_back(new _SunPrivateScripting::SunLuaCFunction<S, T...>(state, name, std::function<S(T...)>(_function)));
    }

    template<typename S, typename... T>
    void registerFunction(_SunPrivateScripting::SunLuaValue value, std::function<S(T...)> _function) {
        functions.push_back(new _SunPrivateScripting::SunLuaCFunction<S, T...>(state, value, _function));
    }

    template<typename S, typename... T>
    void registerFunction(_SunPrivateScripting::SunLuaValue value, S (* _function)(T...)) {
        functions.push_back(new _SunPrivateScripting::SunLuaCFunction<S, T...>(state, value, std::function<S(T...)>(_function)));
    }

    template<typename S, typename... T>
    void registerObject(std::string name, S *object, T... functions) {
        objects.push_back(std::unique_ptr<_SunPrivateScripting::_SunLuaObject_Base>(new _SunPrivateScripting::SunLuaObject<S, T...>(state, name.c_str(), object, functions...)));
    }

    template<typename S, typename... T>
    void registerObject(_SunPrivateScripting::SunLuaValue value, S *object, T... functions) {
        objects.push_back(std::unique_ptr<_SunPrivateScripting::_SunLuaObject_Base>(new _SunPrivateScripting::SunLuaObject<S, T...>(state, value, object, functions...)));
    }

    template<typename T>
    void registerType(std::string type) {

    }

    template<typename... T>
    void registerTypeMembers(std::string type, T... members) {

    }

    template<typename T>
    void registerObjectAsType(std::string name, std::string type, T *object) {

    }

    void printTop() {
        std::cout << std::to_string(state->getTop());
    }

private:
    _SunPrivateScripting::SunLuaState *state;

    std::vector<_SunPrivateScripting::_SunLuaCFunction_Base *> functions;
    std::vector<std::shared_ptr<_SunPrivateScripting::_SunLuaObject_Base>> objects;
};

#endif
