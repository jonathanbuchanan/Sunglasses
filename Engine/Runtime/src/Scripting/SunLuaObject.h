// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUAOBJECT_H
#define SUNLUAOBJECT_H

#include <vector>
#include <memory>

#include "SunLuaObjectFunction.h"

namespace _SunPrivateScripting {
    class _SunLuaObject_Base {

    };
}

template<typename S, typename... T> // S is the class type, T are the functions
class SunLuaObject : public _SunPrivateScripting::_SunLuaObject_Base {
public:
    SunLuaObject(SunLuaState *state, S *object, T... functions) {
        iterateRegister(state, object, functions...);
    }

    template<typename Func, typename... Tail>
    void iterateRegister(SunLuaState *state, S *object, std::string name, Func function, Tail... tail) {
        registerFunction(state, object, name.c_str(), function);
        iterateRegister(state, object, tail...);
    }

    template<typename Func>
    void iterateRegister(SunLuaState *state, S *object, std::string name, Func function) {
        registerFunction(state, object, name.c_str(), function);
    }

private:
    template<typename Ret, typename... Args>
    void registerFunction(SunLuaState *state, S *object, const char *functionName, Ret(S::*function)(Args...)) {
        std::function<Ret(Args...)> lambda = [object, function](Args... args) -> Ret {
            return (object->*function)(args...);
        };
        functions.push_back(std::unique_ptr<_SunPrivateScripting::_SunLuaCFunction_Base>(new SunLuaObjectFunction<Ret, Args...>(state, functionName, lambda)));
    }

    std::vector<std::unique_ptr<_SunPrivateScripting::_SunLuaCFunction_Base>> functions;
};

#endif
