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
#include "SunLuaRawCFunction.h"

namespace _SunPrivateScripting {
    class _SunLuaObject_Base {

    };

    template<typename S, typename... T> // S is the class type, T are the functions
    class SunLuaObject : public _SunPrivateScripting::_SunLuaObject_Base {
    public:
        SunLuaObject(SunLuaState *state, const char *name, S *object, T... functions) {
            members = std::make_tuple(functions...);
            state->newTable();
            iterateRegister(state, object, functions...);
            registerToTable(state, object);
            registerAssignTable(state, object);
            state->setGlobal(name);
        }

        SunLuaObject(SunLuaState *state, SunLuaValue value, S *object, T... functions) {
            members = std::make_tuple(functions...);
            std::vector<_SunPrivateScripting::SunLuaPrimitive> tables = value.getTables();
            if (tables.size() >= 2) {
                state->getGlobal((const char *)tables[0]);
                for (size_t i = 1; i < tables.size() - 1; i++) {
                    tables[i].push(state);
                    state->getTable(-2);
                }
                state->pushString((const char *)tables[tables.size() - 1]);
            }
            state->newTable();
            iterateRegister(state, object, functions...);
            registerToTable(state, object);
            registerAssignTable(state, object);
            if (tables.size() < 2)
                state->setGlobal((const char *)tables[0]);
            else
                state->setTable(-3);
            state->pop(tables.size() - 1);
        }

        template<int... N>
        void beginTable(lua_State *l, S *object, _SunPrivateScripting::seq<N...>) {
            generateTable(l, object, std::get<N>(members)...);
        }

        void generateTable(lua_State *l, S *object) { }

        template<typename Head, typename... Tail>
        void generateTable(lua_State *l, S *object, const char *name, Head head, Tail... tail) {
            luaTableAdd(l, object, name, head);
            generateTable(l, object, tail...);
        }

        template<typename Head>
        void generateTable(lua_State *l, S *object, const char *name, Head head) {
            luaTableAdd(l, object, name, head);
        }

        template<int... N>
        void beginAssignTable(lua_State *l, S *object, seq<N...>) {
            assignTable(l, object, std::get<N>(members)...);
        }

        void assignTable(lua_State *l, S *object) { }

        template<typename Head, typename... Tail>
        void assignTable(lua_State *l, S *object, const char *name, Head head, Tail... tail) {
            luaTableGet(l, object, name, head);
            assignTable(l, object, tail...);
        }

        template<typename Head>
        void assignTable(lua_State *l, S *object, const char *name, Head head) {
            luaTableGet(l, object, name, head);
        }
    private:
        void registerToTable(SunLuaState *state, S *object) {
            std::function<void(lua_State *l)> toTable = [this, object](lua_State *l) -> void {
                lua_newtable(l); // Create table
                beginTable(l, object, typename _SunPrivateScripting::gens<sizeof...(T)>::type());
            };
            functions.push_back(std::unique_ptr<_SunLuaCFunction_Base>(new SunLuaRawCFunction(state, "toTable", toTable, true)));
        }

        void registerAssignTable(SunLuaState *state, S *object) {
            std::function<void(lua_State *l)> assignTable = [this, object](lua_State *l) -> void {
                beginAssignTable(l, object, typename gens<sizeof...(T)>::type());
            };
            functions.push_back(std::unique_ptr<_SunLuaCFunction_Base>(new SunLuaRawCFunction(state, "assignTable", assignTable, true)));
        }

        template<typename Member>
        void luaTableAdd(lua_State *l, S *object, const char *name, Member S::*var) {
            lua_pushstring(l, name);
            SunScripting::pushToStack(l, object->*var);
            lua_settable(l, -3);
        }

        template<typename Ret, typename... Args>
        void luaTableAdd(lua_State *l, S *object, const char *name, Ret(S::*function)(Args...)) {

        }

        template<typename Member>
        void luaTableGet(lua_State *l, S *object, const char *name, Member S::*var) {
            lua_pushstring(l, name);
            lua_gettable(l, -2);
            object->*var = SunScripting::getFromStack<Member>(l, -1);
            lua_pop(l, 1);
        }

        template<typename Ret, typename... Args>
        void luaTableGet(lua_State *l, S *object, const char *name, Ret(S::*function)(Args...)) {

        }

        void iterateRegister(SunLuaState *state, S *object) {

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
            /*char *prefix = (char *)malloc(5); // set_ (4) + NULL (1)
            strcpy(prefix, "set_");
            strcat(prefix, functionName);*/
            const char *prefix = ("set_" + std::string(functionName)).c_str();
            functions.push_back(std::unique_ptr<_SunPrivateScripting::_SunLuaCFunction_Base>(new SunLuaObjectFunction<void, Member>(state, prefix, setter)));
        }

        std::tuple<T...> members;
        std::vector<std::unique_ptr<_SunPrivateScripting::_SunLuaCFunction_Base>> functions;
    };
}

#endif
