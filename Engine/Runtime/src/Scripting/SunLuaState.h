// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUASTATE_H
#define SUNLUASTATE_H

#include "SunLuaPrimitives.h"

#include <string>
#include <map>
#include <algorithm>

#include <lua.hpp>

enum SunLuaBasicType {
    SunLuaTypeInteger,
    SunLuaTypeNumber,
    SunLuaTypeBoolean,
    SunLuaTypeString,
    SunLuaNone
};

namespace _SunPrivateScripting {
    

    class SunLuaState {
    public:
        SunLuaState();
        SunLuaState(const char *file);

        void loadFile(const char *file);

        void close();

        void run(const char *code);

        template<typename T>
        void push(T value) {
            SunScripting::pushToStack(state, value);
        }

        // Lua Functions
        void getGlobal(const char *global);
        void setGlobal(const char *global);
        void newTable();
        void getTable(int index);
        void setTable(int index);

        int getTop();

        int getInteger(int index);
        int getInteger(); // Default Index = -1

        double getNumber(int index);
        double getNumber();

        bool getBoolean(int index);
        bool getBoolean();

        const char * getString(int index);
        const char * getString();

        bool isInteger(int index);
        bool isInteger(); // Default Index = -1

        bool isNumber(int index);
        bool isNumber();

        bool isBoolean(int index);
        bool isBoolean();

        bool isString(int index);
        bool isString();

        bool isTable(int index);
        bool isTable();

        bool isFunction(int index);
        bool isFunction();

        void pushInteger(int x);
        void pushNumber(double x);
        void pushBoolean(bool x);
        void pushString(const char *x);
        void pushLightUserdata(void *data);
        void pushNil();

        void pushCClosure(lua_CFunction function, int upvalues);
        void pushCFunction(lua_CFunction function);

        void pop(int count);
        void pop(); // Default Count = 1
        void remove(int index);

        void callFunction(int argCount, int retCount);

    private:
        lua_State *state; 
    };
}

#endif
