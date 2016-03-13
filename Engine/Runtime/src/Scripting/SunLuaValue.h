// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUAVALUE_H
#define SUNLUAVALUE_H

#include "SunLuaState.h"

#include <lua.hpp>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include <iostream>

namespace _SunPrivateScripting {
    struct SunLuaPrimitive {
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

        void push(SunLuaState *state) {
            switch (type) {
                case Integer:
                    state->pushInteger(i);
                    break;
                case Number:
                    state->pushNumber(n);
                    break;
                case Boolean:
                    state->pushBoolean(b);
                    break;
                case String:
                    state->pushString(s);
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
        SunLuaValue(SunLuaState *s, const char *_var) : state(s), tables() { tables.push_back(_SunPrivateScripting::SunLuaPrimitive(_var)); }
        SunLuaValue(SunLuaState *s, bool _isFunctionReturn, int _index);
        SunLuaValue(SunLuaState *s, std::vector<_SunPrivateScripting::SunLuaPrimitive> _tables, _SunPrivateScripting::SunLuaPrimitive _next) : state(s), tables(_tables) { tables.push_back(_next); }

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
            state->callFunction(count, LUA_MULTRET);
            return SunLuaValue(state, true, -1);
        }

        SunLuaValue operator()() {
            getGlobal();
            state->callFunction(0, LUA_MULTRET);
            return SunLuaValue(state, true, -1);
        }

        void operator=(const int &x);
        void operator=(const double &x);
        void operator=(const bool &x);
        void operator=(const char *x);

        std::vector<_SunPrivateScripting::SunLuaPrimitive> getTables() { return tables; }
    private:
        void getGlobal();
        void cleanGet();

        template<typename S, typename... T>
        void assignResult(S &h, T&... t) {
            int index = -state->getTop();
            h = SunLuaValue(state, true, index);
            assignResult(t...);
        }
        template<typename T>
        void assignResult(T &t) {
            int index = -state->getTop();
            t = SunLuaValue(state, true, index);
        }

        template<typename S, typename... T>
        void passLuaFunctionArguments(S h, T... t) {
            state->push(h);
            passLuaFunctionArguments(t...);
        }
        template<typename T>
        void passLuaFunctionArguments(T t) {
            state->push(t);
        }

        void setUpGetTable();
        void cleanUpGetTable();

        void setUpSetTable();
        void cleanUpSetTable();

        std::vector<_SunPrivateScripting::SunLuaPrimitive> tables;
        int index = -1;
        bool isFunctionReturn = false;
        SunLuaState *state;
    };
}

#endif
