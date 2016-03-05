// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNSCRIPT_H
#define SUNSCRIPT_H

#include <lua.hpp>

#include "SunLuaValue.h"
#include "SunLuaState.h"
#include "SunLuaCFunction.h"

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
        SunLuaCFunction<S, T...> *function = new SunLuaCFunction<S, T...>(name, _function);
        function->registerAsFunction(state);
        functions.push_back((_SunPrivateScripting::_SunLuaCFunction_Base *)function);
    }

    template<typename S, typename... T>
    void registerFunction(std::string name, S (* _function)(T...)) {
        SunLuaCFunction<S, T...> *function = new SunLuaCFunction<S, T...>(name, std::function<S(T...)>(_function));
        function->registerAsFunction(state);
        functions.push_back((_SunPrivateScripting::_SunLuaCFunction_Base *)function);
    }

    SunLuaState * getState() { return state; }
private:
    SunLuaState *state;

    std::vector<_SunPrivateScripting::_SunLuaCFunction_Base *> functions;
};

#endif
