// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNSCRIPT_H
#define SUNSCRIPT_H

#include <map>
#include <memory>
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

    SunLuaValue getVariable(std::string var);
    SunLuaValue operator[](std::string var);

    void run(std::string code);
    void operator()(std::string code);

    template<typename S, typename... T>
    void registerFunction(std::string name, std::function<S(T...)> _function) {
        functions.push_back(new SunLuaCFunction<S, T...>(state, name, _function));
    }

    template<typename S, typename... T>
    void registerFunction(std::string name, S (* _function)(T...)) {
        functions.push_back(new SunLuaCFunction<S, T...>(state, name, std::function<S(T...)>(_function)));
    }

    template<typename S, typename... T>
    void registerFunction(SunLuaValue value, std::function<S(T...)> _function) {
        functions.push_back(new SunLuaCFunction<S, T...>(state, value, _function));
    }

    template<typename S, typename... T>
    void registerFunction(SunLuaValue value, S (* _function)(T...)) {
        functions.push_back(new SunLuaCFunction<S, T...>(state, value, std::function<S(T...)>(_function)));
    }

    template<typename S, typename... T>
    void registerObject(std::string name, S *object, T... functions) {
        objects.push_back(std::unique_ptr<_SunPrivateScripting::_SunLuaObject_Base>(new SunLuaObject<S, T...>(state, name.c_str(), object, functions...)));
    }

    template<typename S, typename... T>
    void registerObject(SunLuaValue value, S *object, T... functions) {
        objects.push_back(std::unique_ptr<_SunPrivateScripting::_SunLuaObject_Base>(new SunLuaObject<S, T...>(state, value, object, functions...)));
    }

    SunLuaState * getState() { return state; }
private:
    SunLuaState *state;

    std::vector<_SunPrivateScripting::_SunLuaCFunction_Base *> functions;
    std::vector<std::unique_ptr<_SunPrivateScripting::_SunLuaObject_Base>> objects;
};

#endif
