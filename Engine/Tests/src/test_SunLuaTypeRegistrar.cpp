// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Sunglasses/Sunglasses.hpp>

struct TestClass {
    int x;
    float y;
    std::string z;

    void increment(int amount) {
        x += amount;
    }

    int doubleX() {
        return x * 2;
    }
};
template<> const std::string SunLuaTypeRegistrar<TestClass>::typeName = "TestClass";
template<> const std::vector<SunScripting::SunLuaTypeDataMemberBase<TestClass> *> SunLuaTypeRegistrar<TestClass>::dataMembers = {
    new SunLuaTypeDataMember<int, TestClass>("x", &TestClass::x),
    new SunLuaTypeDataMember<float, TestClass>("y", &TestClass::y),
    new SunLuaTypeDataMember<std::string, TestClass>("z", &TestClass::z),
    new SunLuaTypeMemberFunction<TestClass, void, int>("increment", &TestClass::increment),
    new SunLuaTypeMemberFunction<TestClass, int>("doubleX", &TestClass::doubleX)
};

struct SunLuaTypeRegistrarTest : ::testing::Test {
    lua_State *L;

    SunLuaTypeRegistrarTest() {
        L = luaL_newstate();
        luaL_openlibs(L);
        SunLuaTypeRegistrar<TestClass>::registerInState(L);
        luaL_dostring(L, "foo = TestClass({x = 10, y = 20.5, z = \"Hello, World!\"})");
    }

    virtual ~SunLuaTypeRegistrarTest() {
        lua_close(L);
    }
};

TEST_F(SunLuaTypeRegistrarTest, Constructor) {
    lua_getglobal(L, "foo");

    lua_pushstring(L, "x");
    lua_gettable(L, -2);
    EXPECT_EQ(10, (int)lua_tonumber(L, -1));
    lua_pop(L, 1);

    lua_pushstring(L, "y");
    lua_gettable(L, -2);
    EXPECT_DOUBLE_EQ(20.5, (double)lua_tonumber(L, -1));
    lua_pop(L, 1);

    lua_pushstring(L, "z");
    lua_gettable(L, -2);
    EXPECT_STREQ("Hello, World!", (const char *)lua_tostring(L, -1));
    lua_pop(L, 1);

    lua_pop(L, 1);
}

TEST_F(SunLuaTypeRegistrarTest, Methods) {
    luaL_dostring(L, "foo.increment(5)");

    luaL_dostring(L, "x = foo.doubleX()");
    lua_getglobal(L, "x");
    int x = lua_tointeger(L, -1);
    lua_pop(L, 1);
    EXPECT_EQ(x, 30);
}
