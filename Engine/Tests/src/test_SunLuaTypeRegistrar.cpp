#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Sunglasses/Sunglasses.hpp>

struct TestClass {
    int x;
    float y;
    std::string z;
};
template<> const std::string SunLuaTypeRegistrar<TestClass>::typeName = "TestClass";
template<> const std::vector<SunScripting::SunLuaTypeDataMemberBase<TestClass> *> SunLuaTypeRegistrar<TestClass>::dataMembers = {
    new SunLuaTypeDataMember<int, TestClass>("x", &TestClass::x),
    new SunLuaTypeDataMember<float, TestClass>("y", &TestClass::y),
    new SunLuaTypeDataMember<std::string, TestClass>("z", &TestClass::z)
};

struct SunLuaTypeRegistrarTest : ::testing::Test {
    lua_State *L;

    SunLuaTypeRegistrarTest() {
        L = luaL_newstate();
        luaL_openlibs(L);
        SunLuaTypeRegistrar<TestClass>::registerInState(L);
    }

    virtual void TearDown() {
        lua_close(L);
    }
};

TEST_F(SunLuaTypeRegistrarTest, Constructor) {
    luaL_dostring(L, "foo = TestClass({x = 10, y = 20.5, z = \"Hello, World!\"})");

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
