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

    template<typename Ret, typename... Args>
    void registerFunction(SunLuaState *state, S *object, const char *functionName, Ret(S::*function)(Args...)) {
        std::function<Ret(Args...)> lambda = [object, function](Args... args) -> Ret {
            return (object->*function)(args...);
        };
        functions.push_back(new SunLuaObjectFunction<Ret, Args...>(functionName, lambda));
    }
private:
    std::vector<std::unique_ptr<_SunPrivateScripting::_SunLuaCFunction_Base>> functions;
};

#endif
