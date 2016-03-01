#ifndef SUNLUAVALUE_H
#define SUNLUAVALUE_H

#include <lua.hpp>
#include <string>

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

    void operator=(const int &x);
    void operator=(const double &x);
    void operator=(const bool &x);
    void operator=(const char *x);

private:
    void getGlobal();
    void cleanGet();

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
