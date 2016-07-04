// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUACFUNCTION_H
#define SUNLUACFUNCTION_H

#include <string>
#include <functional>
#include <tuple>
#include <vector>
#include <iostream>

#include <lua.hpp>

#include <sunglasses/Scripting/SunLuaValue.h>

namespace _SunPrivateScripting {
    class _SunLuaCFunction_Base {
    public:
        virtual void run(lua_State *state) = 0;
    };

    extern int callFunction(lua_State *state);

    template<typename Function, typename Tuple, int... N>
    struct test {
        static void exec(Function f, Tuple tuple) {
            f(std::get<N>(tuple)...);
        }
    };

    template<int...>
    struct seq {

    };

    template<int N, int... S>
    struct gens : gens<N - 1, N - 1, S...> {

    };

    template<int... S>
    struct gens<0, S...> {
        typedef seq<S...> type;
    };

    template<typename S, typename... T>
    class SunLuaCFunction : public _SunPrivateScripting::_SunLuaCFunction_Base {
    public:
        SunLuaCFunction(lua_State *state, std::string _name, std::function<S(T...)> _function) {
            name = _name;
            function = _function;
            registerAsFunction(state);
        }

        SunLuaCFunction(lua_State *state, SunLuaValue value, std::function<S(T...)> _function) {
            function = _function;
            registerAsFunction(state, value);
        }

        void run(lua_State *state) {
            S result = execute(getArguments(state), typename _SunPrivateScripting::gens<sizeof...(T)>::type());
            SunScripting::pushToStack(state, result);
        }

        void registerAsFunction(lua_State *state, SunLuaValue value) {
            std::vector<_SunPrivateScripting::SunLuaPrimitive> tables = value.getTables();
            if (tables.size() >= 2) {
                lua_getglobal(state, (const char *)tables[0]);
                for (int i = 1; i < tables.size() - 1; i++) {
                    tables[i].push(state);
                    lua_gettable(state, -2);
                }
            }
            if (tables.size() < 2) {
                lua_pushlightuserdata(state, (void *)static_cast<_SunPrivateScripting::_SunLuaCFunction_Base *>(this));
                lua_pushcclosure(state, &_SunPrivateScripting::callFunction, 1);
                lua_setglobal(state, (const char *)tables[0]);
            } else {
                lua_pushstring(state, (const char *)tables[tables.size() - 1]); // Push name of function
                lua_pushlightuserdata(state, (void *)static_cast<_SunPrivateScripting::_SunLuaCFunction_Base *>(this)); // Upvalue pointer to this
                lua_pushcclosure(state, &_SunPrivateScripting::callFunction, 1); // Push C Closure
                lua_settable(state, -3);
            }
            lua_pop(state, tables.size());
        }

        void registerAsFunction(lua_State *state) {
            lua_pushlightuserdata(state, (void *)this);
            lua_pushcclosure(state, &_SunPrivateScripting::callFunction, 1);
            lua_setglobal(state, name.c_str());
        }

        void setName(std::string n) { name = n; }
        template<typename Return, typename... Args>
        void setFunction(std::function<Return(Args...)> f) { function = f; }
    private:
        template<int... N>
        S execute(std::tuple<T...> tuple, _SunPrivateScripting::seq<N...>) {
            return (S)function(std::get<N>(tuple)...);
        }

        template<int... N>
        std::tuple<T...> getArguments(lua_State *l, _SunPrivateScripting::seq<N...>) {
            return std::make_tuple(SunScripting::getFromStack<T>(l, N + 1)...);
        }

        std::tuple<T...> getArguments(lua_State *l) {
            return getArguments(l, typename _SunPrivateScripting::gens<sizeof...(T)>::type());
        }

        std::string name;
        std::function<S(T...)> function;
    };


    // Partial Specialization of SunLuaCFunction for void returns
    /*template<typename... T>
    class SunLuaCFunction<void, T...> : public _SunPrivateScripting::_SunLuaCFunction_Base {
    private:
        template<int... N>
        void execute(std::tuple<T...> tuple, _SunPrivateScripting::seq<N...>) {
            function(std::get<N>(tuple)...);
        }

        std::function<void(T...)> function;
    };*/
    /*template<typename... T, int... N>

    void SunLuaCFunction<void, T...>::execute(std::tuple<T...> tuple, _SunPrivateScripting::seq<N...>) {
        function(std::get<N>(tuple)...);
    }*/
}

#endif
