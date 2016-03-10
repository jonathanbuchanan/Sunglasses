// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUAOBJECT_H
#define SUNLUAOBJECT_H

#include <vector>
#include <memory>
#include <string.h>

#include "SunLuaObjectFunction.h"
#include "SunLuaValue.h"

namespace _SunPrivateScripting {
    class _SunLuaObject_Base {

    };

    template<typename S, typename... T> // S is the class type, T are the functions
    class SunLuaObject : public _SunPrivateScripting::_SunLuaObject_Base {
    public:
        SunLuaObject(SunLuaState *state, const char *name, S *object, T... functions) {
            state->newTable();
            iterateRegister(state, object, functions...);
            state->setGlobal(name);
        }

        SunLuaObject(SunLuaState *state, SunLuaValue value, S *object, T... functions) {
            std::vector<_SunPrivateScripting::SunLuaType> tables = value.getTables();
            if (tables.size() >= 2) {
                state->getGlobal((const char *)tables[0]);
                for (int i = 1; i < tables.size() - 1; i++) {
                    tables[i].push(state);
                    state->getTable(-2);
                }
                state->pushString((const char *)tables[tables.size() - 1]);
            }
            state->newTable();
            iterateRegister(state, object, functions...);
            if (tables.size() < 2)
                state->setGlobal((const char *)tables[0]);
            else
                state->setTable(-3);
            state->pop(tables.size());
        }
    private:
        template<typename Func, typename... Tail>
        void iterateRegister(SunLuaState *state, S *object, std::string name, Func function, Tail... tail) {
            registerFunction(state, object, name.c_str(), function);
            iterateRegister(state, object, tail...);
        }

        template<typename Func>
        void iterateRegister(SunLuaState *state, S *object, std::string name, Func function) {
            registerFunction(state, object, name.c_str(), function);
        }

        template<typename Ret, typename... Args>
        void registerFunction(SunLuaState *state, S *object, const char *functionName, Ret(S::*function)(Args...)) {
            std::function<Ret(Args...)> lambda = [object, function](Args... args) -> Ret {
                return (object->*function)(args...);
            };
            functions.push_back(std::unique_ptr<_SunPrivateScripting::_SunLuaCFunction_Base>(new SunLuaObjectFunction<Ret, Args...>(state, functionName, lambda)));
        }

        template<typename Member>
        void registerFunction(SunLuaState *state, S *object, const char *functionName, Member S::*var) {
            std::function<Member()> getter = [object, var]() -> Member {
                return object->*var;
            };
            functions.push_back(std::unique_ptr<_SunPrivateScripting::_SunLuaCFunction_Base>(new SunLuaObjectFunction<Member>(state, functionName, getter)));
            std::function<void(Member)> setter = [object, var](Member x) -> void {
                object->*var = x;
            };
            char *prefix = (char *)malloc(5); // set_ (4) + NULL (1)
            strcpy(prefix, "set_");
            strcat(prefix, functionName);
            functions.push_back(std::unique_ptr<_SunPrivateScripting::_SunLuaCFunction_Base>(new SunLuaObjectFunction<void, Member>(state, prefix, setter)));
        }

        std::vector<std::unique_ptr<_SunPrivateScripting::_SunLuaCFunction_Base>> functions;
    };
}

#endif
