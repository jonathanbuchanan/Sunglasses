// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef LUAVALUE_H
#define LUAVALUE_H

#include <sunglasses/Scripting/LuaPrimitives.h>

#include <lua.hpp>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include <iostream>

namespace sunglasses {

namespace _PrivateScripting {
    struct LuaPrimitive {
        LuaPrimitive() { }
        LuaPrimitive(int x) : i(x) { type = Integer; }
        LuaPrimitive(double x) : n(x) { type = Number; }
        LuaPrimitive(bool x) : b(x) { type = Boolean; }
        LuaPrimitive(const char *x) : s(x) { type = String; }

        operator int() {
            return i;
        }

        operator double() {
            return n;
        }

        operator bool() {
            return b;
        }

        operator const char *() {
            return s;
        }

        void push(lua_State *state) {
            switch (type) {
                case Integer:
                    lua_pushinteger(state, i);
                    break;
                case Number:
                    lua_pushnumber(state, n);
                    break;
                case Boolean:
                    lua_pushboolean(state, b);
                    break;
                case String:
                    lua_pushstring(state, s);
                    break;
            }
        }

        enum {
            Integer,
            Number,
            Boolean,
            String
        } type;
        union {
            int i;
            double n;
            bool b;
            const char *s;
        };
    };


    class LuaValue {
    public:
        LuaValue(lua_State *s, const char *_var) : tables(), index(-1), isFunctionReturn(false), state(s) { tables.push_back(_PrivateScripting::LuaPrimitive(_var)); }
        LuaValue(lua_State *s, bool _isFunctionReturn, int _index);
        LuaValue(lua_State *s, std::vector<_PrivateScripting::LuaPrimitive> _tables, _PrivateScripting::LuaPrimitive _next) :  tables(_tables), index(-1), isFunctionReturn(false), state(s) { tables.push_back(_next); }

        void newTable();

        operator int();
        operator double();
        operator bool();
        operator std::string();

        template<typename... T>
        void assign(T&... references) {
            assignResult(references...);
        }

        LuaValue operator[](const int &element);
        LuaValue operator[](const double &element);
        LuaValue operator[](const bool &element);
        LuaValue operator[](const char *element);

        template<typename... T>
        LuaValue operator()(T... args) {
            getGlobal();
            passLuaFunctionArguments(args...);
            const int count = sizeof...(T);
            lua_call(state, count, LUA_MULTRET);
            return LuaValue(state, true, -1);
        }

        LuaValue operator()() {
            getGlobal();
            lua_call(state, 0, LUA_MULTRET);
            return LuaValue(state, true, -1);
        }

        void operator=(const int &x);
        void operator=(const double &x);
        void operator=(const bool &x);
        void operator=(const char *x);

        void setNil();

        std::vector<_PrivateScripting::LuaPrimitive> getTables() { return tables; }
    private:
        void getGlobal();
        void cleanGet();

        template<typename S, typename... T>
        void assignResult(S &h, T&... t) {
            int index = -lua_gettop(state);
            h = LuaValue(state, true, index);
            assignResult(t...);
        }
        template<typename T>
        void assignResult(T &t) {
            int index = -lua_gettop(state);
            t = LuaValue(state, true, index);
        }

        template<typename S, typename... T>
        void passLuaFunctionArguments(S h, T... t) {
            Scripting::pushToStack(state, h);
            passLuaFunctionArguments(t...);
        }
        template<typename T>
        void passLuaFunctionArguments(T t) {
            Scripting::pushToStack(state, t);
        }

        void setUpGetTable();
        void cleanUpGetTable();

        void setUpSetTable();
        void cleanUpSetTable();

        std::vector<_PrivateScripting::LuaPrimitive> tables;
        int index;
        bool isFunctionReturn;
        lua_State *state;
    };
}

} // namespace

#endif
