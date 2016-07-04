// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUAVALUE_H
#define SUNLUAVALUE_H

#include <sunglasses/Scripting/SunLuaPrimitives.h>

#include <lua.hpp>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include <iostream>

namespace _SunPrivateScripting {
    struct SunLuaPrimitive {
        SunLuaPrimitive() { }
        SunLuaPrimitive(int x) : i(x) { type = Integer; }
        SunLuaPrimitive(double x) : n(x) { type = Number; }
        SunLuaPrimitive(bool x) : b(x) { type = Boolean; }
        SunLuaPrimitive(const char *x) : s(x) { type = String; }

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


    class SunLuaValue {
    public:
        SunLuaValue(lua_State *s, const char *_var) : tables(), index(-1), isFunctionReturn(false), state(s) { tables.push_back(_SunPrivateScripting::SunLuaPrimitive(_var)); }
        SunLuaValue(lua_State *s, bool _isFunctionReturn, int _index);
        SunLuaValue(lua_State *s, std::vector<_SunPrivateScripting::SunLuaPrimitive> _tables, _SunPrivateScripting::SunLuaPrimitive _next) :  tables(_tables), index(-1), isFunctionReturn(false), state(s) { tables.push_back(_next); }

        void newTable();

        operator int();
        operator double();
        operator bool();
        operator std::string();

        template<typename... T>
        void assign(T&... references) {
            assignResult(references...);
        }

        SunLuaValue operator[](const int &element);
        SunLuaValue operator[](const double &element);
        SunLuaValue operator[](const bool &element);
        SunLuaValue operator[](const char *element);

        template<typename... T>
        SunLuaValue operator()(T... args) {
            getGlobal();
            passLuaFunctionArguments(args...);
            const int count = sizeof...(T);
            lua_call(state, count, LUA_MULTRET);
            return SunLuaValue(state, true, -1);
        }

        SunLuaValue operator()() {
            getGlobal();
            lua_call(state, 0, LUA_MULTRET);
            return SunLuaValue(state, true, -1);
        }

        void operator=(const int &x);
        void operator=(const double &x);
        void operator=(const bool &x);
        void operator=(const char *x);

        void setNil();

        std::vector<_SunPrivateScripting::SunLuaPrimitive> getTables() { return tables; }
    private:
        void getGlobal();
        void cleanGet();

        template<typename S, typename... T>
        void assignResult(S &h, T&... t) {
            int index = -lua_gettop(state);
            h = SunLuaValue(state, true, index);
            assignResult(t...);
        }
        template<typename T>
        void assignResult(T &t) {
            int index = -lua_gettop(state);
            t = SunLuaValue(state, true, index);
        }

        template<typename S, typename... T>
        void passLuaFunctionArguments(S h, T... t) {
            SunScripting::pushToStack(state, h);
            passLuaFunctionArguments(t...);
        }
        template<typename T>
        void passLuaFunctionArguments(T t) {
            SunScripting::pushToStack(state, t);
        }

        void setUpGetTable();
        void cleanUpGetTable();

        void setUpSetTable();
        void cleanUpSetTable();

        std::vector<_SunPrivateScripting::SunLuaPrimitive> tables;
        int index;
        bool isFunctionReturn;
        lua_State *state;
    };
}

#endif
