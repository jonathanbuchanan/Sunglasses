// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNSCRIPT_H
#define SUNSCRIPT_H

#include <lua.hpp>

#include "SunLuaValue.h"
#include "SunLuaState.h"

class SunScript {
public:
    SunScript();
    ~SunScript();

    void loadFile(std::string file);

    SunLuaValue getVariable(std::string var);
    SunLuaValue operator[](std::string var);

    void run(std::string code);
    void operator()(std::string code);

    /*inline sel::Selector operator[](const char *name) { return state[name]; }
    inline sel::Selector getElement(const char *name) { return state[name]; }
    inline sel::Selector getObject(const char *name) { return state[name]; }
    inline sel::Selector getVariable(const char *name) { return state[name]; }
    inline sel::Selector getFunction(const char *name) { return state[name]; }

    void run(const char *code);
    void operator()(const char *code);

    template<typename N, typename... T> // Register std::function
    void registerFunction(const char *name, std::function<N(T...)> function) {
        state[name] = function;
    }
    template<typename T> // Register lambda
    void registerFunction(const char *name, T lambda) {
        state[name] = lambda;
    }
    template<typename N, typename... T> // Register C Function
    void registerFunction(const char *name, N (* function)(T...)) {
        state[name] = function;
    }

    template<typename M, typename N, typename... T>
    void registerClass(const char *name, T... functions) {
        state[name].SetClass<M, N>(functions...);
    }

    template<typename N, typename... T>
    void registerObject(const char *name, N &object, T... functions) {
        state[name].SetObj(object, functions...);
    }*/
private:
    SunLuaState *state;
};

#endif
