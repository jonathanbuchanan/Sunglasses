// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Sunglasses.hpp>

struct SunLuaPrimitivesTest : ::testing::Test {
    lua_State *L;

    SunLuaPrimitivesTest() {
        L = luaL_newstate();
        luaL_openlibs(L);
    }

    virtual ~SunLuaPrimitivesTest() {
        lua_close(L);
    }
};

TEST_F(SunLuaPrimitivesTest, Push) {
    // One of each type
    int a = 42;
    double pi = 3.14159265;
    float e = 2.71828;
    bool yes = true;
    const char *string = "Hello, World!";

    // Int
    SunScripting::pushToStack(L, a);
    EXPECT_EQ(lua_isinteger(L, -1), true);
    EXPECT_EQ(lua_tointeger(L, -1), 42);
    lua_pop(L, 1);

    // Double
    SunScripting::pushToStack(L, pi);
    EXPECT_EQ(lua_isnumber(L, -1), true);
    EXPECT_DOUBLE_EQ(lua_tonumber(L, -1), 3.14159265);
    lua_pop(L, 1);

    // Float
    SunScripting::pushToStack(L, e);
    EXPECT_EQ(lua_isnumber(L, -1), true);
    EXPECT_FLOAT_EQ((float)lua_tonumber(L, -1), 2.71828);
    lua_pop(L, 1);

    // Bool
    SunScripting::pushToStack(L, yes);
    EXPECT_EQ(lua_isboolean(L, -1), true);
    EXPECT_EQ(lua_toboolean(L, -1), true);
    lua_pop(L, 1);

    // String
    SunScripting::pushToStack(L, string);
    EXPECT_EQ(lua_isstring(L, -1), true);
    EXPECT_STREQ(lua_tostring(L, -1), "Hello, World!");
    lua_pop(L, 1);
}

TEST_F(SunLuaPrimitivesTest, Get) {
    // One of each type
    int x = 1234321;
    double roottwo = 1.4142135624;
    float sin60 = 0.866025;
    bool no = false;
    const char *string = "ABCDEF!!!";

    // Int
    lua_pushinteger(L, x);
    EXPECT_EQ(SunScripting::getFromStack<int>(L, -1), 1234321);
    lua_pop(L, 1);

    // Double
    lua_pushnumber(L, roottwo);
    EXPECT_DOUBLE_EQ(SunScripting::getFromStack<double>(L, -1), 1.4142135624);
    lua_pop(L, 1);

    // Float
    lua_pushnumber(L, sin60);
    EXPECT_FLOAT_EQ(SunScripting::getFromStack<float>(L, -1), 0.866025);
    lua_pop(L, 1);

    // Bool
    lua_pushboolean(L, no);
    EXPECT_EQ(SunScripting::getFromStack<bool>(L, -1), false);
    lua_pop(L, 1);

    // String
    lua_pushstring(L, string);
    EXPECT_STREQ(SunScripting::getFromStack<const char *>(L, -1), "ABCDEF!!!");
    lua_pop(L, 1);
} 
