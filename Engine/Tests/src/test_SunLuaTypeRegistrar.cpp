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
template<> const std::map<std::string, SunScripting::SunLuaTypeDataMemberBase<TestClass> *> SunLuaTypeRegistrar<TestClass>::dataMembers = {
    {"x", new SunLuaTypeDataMember<int, TestClass>("x", &TestClass::x)},
    {"y", new SunLuaTypeDataMember<float, TestClass>("y", &TestClass::y)},
    {"z", new SunLuaTypeDataMember<std::string, TestClass>("z", &TestClass::z)},
    {"increment", new SunLuaTypeMemberFunction<TestClass, void, int>("increment", &TestClass::increment)},
    {"doubleX", new SunLuaTypeMemberFunction<TestClass, int>("doubleX", &TestClass::doubleX)}
};
template<> const std::string SunLuaTypeRegistrar<TestClass>::memberTableName = "__members";

struct SunLuaTypeRegistrarTest : ::testing::Test {
    lua_State *L;
    TestClass *obj;

    SunLuaTypeRegistrarTest() {
        L = luaL_newstate();
        luaL_openlibs(L);
        SunLuaTypeRegistrar<TestClass>::registerInState(L);
        luaL_dostring(L, "foo = TestClass({x = 10, y = 20.5, z = \"Hello, World!\"})");

        obj = new TestClass();
        obj->x = 10;
        obj->y = 1.23;
        obj->z = "TESTING";

        SunLuaTypeRegistrar<TestClass>::registerObject(L, "obj", obj);
    }

    virtual ~SunLuaTypeRegistrarTest() {
        delete obj;
        lua_close(L);
    }
};

TEST_F(SunLuaTypeRegistrarTest, AccessMembers) {
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

    luaL_dostring(L, "foo.increment(5)");
    lua_pushstring(L, "x");
    lua_gettable(L, -2);
    EXPECT_EQ(15, (int)lua_tonumber(L, -1));
    lua_pop(L, 1);

    luaL_dostring(L, "x = foo.doubleX()");
    lua_getglobal(L, "x");
    int x = lua_tointeger(L, -1);
    lua_pop(L, 1);
    EXPECT_EQ(x, 30);

    lua_pop(L, 1);
}

TEST_F(SunLuaTypeRegistrarTest, WriteMembers) {
    lua_getglobal(L, "foo");

    luaL_dostring(L, "foo.x = 220");
    
    lua_pushstring(L, "x");
    lua_gettable(L, -2);
    EXPECT_EQ(220, (int)lua_tonumber(L, -1));
    lua_pop(L, 1);

    luaL_dostring(L, "foo.y = 3.1415");
    
    lua_pushstring(L, "y");
    lua_gettable(L, -2);
    EXPECT_FLOAT_EQ(3.1415, (double)lua_tonumber(L, -1));
    lua_pop(L, 1);

    luaL_dostring(L, "foo.z = \"This is a test\"");

    lua_pushstring(L, "z");
    lua_gettable(L, -2);
    EXPECT_STREQ("This is a test", (const char *)lua_tostring(L, -1));
    lua_pop(L, 1);
}

TEST_F(SunLuaTypeRegistrarTest, RegisterObjects) {
    lua_getglobal(L, "obj");

    lua_getfield(L, -1, "x");
    EXPECT_EQ(10, (int)lua_tonumber(L, -1));
    lua_pop(L, 1);

    lua_getfield(L, -1, "y");
    EXPECT_FLOAT_EQ(1.23, (double)lua_tonumber(L, -1));
    lua_pop(L, 1);

    lua_getfield(L, -1, "z");
    EXPECT_STREQ("TESTING", (const char *)lua_tostring(L, -1));
    lua_pop(L, 1);

    luaL_dostring(L, "obj.increment(111)");

    lua_getfield(L, -1, "x");
    EXPECT_EQ(121, (int)lua_tonumber(L, -1));
    lua_pop(L, 1);

    lua_pop(L, 1);
}
