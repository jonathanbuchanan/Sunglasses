#ifndef SUNLUAVALUE_H
#define SUNLUAVALUE_H

#include <lua.hpp>
#include <string>
#include <vector>
#include <utility>
#include <typeinfo>

// Temp
#include <iostream>
// Temp

enum SunLuaValueBasicType {
    SunLuaValueTypeInteger,
    SunLuaValueTypeNumber,
    SunLuaValueTypeBoolean,
    SunLuaValueTypeString
};

class SunLuaValue {
public:
    SunLuaValue(lua_State *s, const char *_var);
    SunLuaValue(lua_State *s, const char *_var, bool _i, SunLuaValue *p);

    void newTable();

    operator int();
    operator double();
    operator bool();
    operator std::string();

    SunLuaValue operator[](const int element);
    SunLuaValue operator[](const double element);
    SunLuaValue operator[](const bool element);
    SunLuaValue operator[](const char *element);

    template<typename... T>
    SunLuaValue operator()(T &... args) {
        lua_getglobal(state, var);
        int a = 0;
        if (typeid(a) == typeid(int))
            std::cout << "hi" << std::endl;
    }

    void operator=(const int &x);
    void operator=(const double &x);
    void operator=(const bool &x);
    void operator=(const char *x);

private:
    void getGlobal();
    void cleanGet();

    template<typename Head, typename... Tail>
    void passLuaFunctionArguments(Head h, Tail... t) {

    }

    void setUpGetTable(const char *key);
    void cleanUpGetTable();

    void setUpSetTable(const char *key);
    void cleanUpSetTable();

    int level = 0;
    bool isTable = false;
    bool isTableValue = false;
    SunLuaValue *parentTable;
    const char *var;
    lua_State *state;
};

#endif
