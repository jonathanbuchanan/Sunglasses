// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUASTATE_H
#define SUNLUASTATE_H

#include <string>
#include <map>
#include <algorithm>
#include <typeinfo>
#include <typeindex>

#include <lua.hpp>

enum SunLuaBasicType {
    SunLuaTypeInteger,
    SunLuaTypeNumber,
    SunLuaTypeBoolean,
    SunLuaTypeString,
    SunLuaNone
};

namespace _SunPrivateScripting {
    template<typename T>
    T get(lua_State *l, int index);

    template<> int get(lua_State *l, int index);
    template<> double get(lua_State *l, int index);
    template<> float get(lua_State *l, int index);
    template<> bool get(lua_State *l, int index);
    template<> const char * get(lua_State *l, int index);



    template<typename T>
    void push(lua_State *l, T value);

    template<> void push(lua_State *l, int value);
    template<> void push(lua_State *l, double value);
    template<> void push(lua_State *l, float value);
    template<> void push(lua_State *l, bool value);
    template<> void push(lua_State *l, const char *value);
    template<> void push(lua_State *l, char *value);
}

class SunLuaState {
public:
    SunLuaState();
    SunLuaState(const char *file);

    void loadFile(const char *file);

    void run(const char *code);

    template<typename T> SunLuaBasicType getType() {
        if (typeMap.find(std::type_index(typeid(T))) != typeMap.end())
            return typeMap[std::type_index(typeid(T))];
        else
            return SunLuaNone;
    }
    template<typename T> SunLuaBasicType getType(T x) { return getType<T>(); }

    template<typename T>
    void push(T value) {
        _SunPrivateScripting::push(state, value);
    }
    /*template<typename T> int push(T x) {
        switch (getType<T>()) {
            case SunLuaTypeInteger:
                pushInteger((int)x);
                break;
            case SunLuaTypeNumber:
                pushNumber((double)x);
                break;
            case SunLuaTypeBoolean:
                pushBoolean((bool)x);
                break;
            case SunLuaTypeString:
                pushString((const char *)x);
                break;
            case SunLuaNone:
                return -1;
                break;
        }
    }*/

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

    void pushCClosure(lua_CFunction function, int upvalues);

    void pop(int count);
    void pop(); // Default Count = 1
    void remove(int index);

    void callFunction(int argCount, int retCount);

private:
    lua_State *state;

    std::map<std::type_index, SunLuaBasicType> typeMap = {
        {std::type_index(typeid(int)), SunLuaTypeInteger},

        {std::type_index(typeid(float)), SunLuaTypeNumber},
        {std::type_index(typeid(double)), SunLuaTypeNumber},

        {std::type_index(typeid(bool)), SunLuaTypeBoolean},

        {std::type_index(typeid(const char *)), SunLuaTypeString}
    };
};

#endif
