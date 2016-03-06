// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUACLASS_H
#define SUNLUACLASS_H

#include <vector>
#include <memory>

#include "SunLuaClassFunction.h"

namespace _SunPrivateScripting {
    class _SunLuaClass_Base {

    };
}

template<typename S, typename... T> // S is the class type, T are the functions
class SunLuaClass : public _SunPrivateScripting::_SunLuaClass_Base {
public:

    template<typename Ret, typename... Args>
    void registerFunction(SunLuaState *state, S *object, const char *functionName, Ret(S::*function)(Args...)) {
        std::function<Ret(Args...)> lambda = [object, function](Args... args) -> Ret {
            return (object->*function)(args...);
        };
        functions.push_back(new SunLuaClassFunction<Ret, Args...>(functionName, lambda));
    }
private:
    std::vector<std::unique_ptr<_SunPrivateScripting::_SunLuaCFunction_Base>> functions;
};

#endif
