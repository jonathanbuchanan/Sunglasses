// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Sunglasses/Sunglasses.hpp>

struct SunScriptTest : ::testing::Test {
    SunScript script;
    SunScriptTest() {
        script.loadFile("test_SunScript_0.lua");
        script.loadFile("test_SunScript_1.lua");
    }

    virtual void TearDown() {
        
    }
};

TEST_F(SunScriptTest, LuaVariables) {
    int x = script.getVariable("x");
    EXPECT_EQ(x, 2);

    double pi = script["pi"];
    EXPECT_DOUBLE_EQ(pi, 3.14);

    bool yes = script.getVariable("yes");
    EXPECT_EQ(yes, true);

    bool no = script.getVariable("no");
    EXPECT_EQ(no, false);

    std::string str = script.getVariable("str");
    EXPECT_EQ(str, "Hello, World!");

    int a = script["table"]["a"];
    EXPECT_EQ(a, 7);

    double b = script.getVariable("table")["b"];
    EXPECT_DOUBLE_EQ(b, 1.23);

    bool c = script.getVariable("table")["c"];
    EXPECT_EQ(c, true);

    bool d = script.getVariable("table")["d"];
    EXPECT_EQ(d, false);

    EXPECT_EQ((std::string)script["table"]["e"], "Test");

    int r = script["table"]["f"]["r"];
    EXPECT_EQ(r, 1);

    double g = script["table"]["f"]["g"];
    EXPECT_DOUBLE_EQ(g, 0.2);

    double b_ = script["table"]["f"]["b"];
    EXPECT_DOUBLE_EQ(b_, 0.5);

    script["a"] = 23;
    EXPECT_EQ((int)script["a"], 23);

    script["b"] = 3.21;
    EXPECT_DOUBLE_EQ((double)script["b"], 3.21);

    script["c"] = true;
    EXPECT_EQ((bool)script["c"], true);

    script["d"] = false;
    EXPECT_EQ((bool)script["d"], false);

    script["e"] = "Testing";
    EXPECT_EQ((std::string)script["e"], "Testing");

    script["table"]["o"].newTable();

    script["table"]["o"][1] = -3;
    EXPECT_EQ((int)script["table"]["o"][1], -3);

    script["table"]["o"][2] = true;
    EXPECT_EQ((bool)script["table"]["o"][2], true);

    script["table"]["o"][3] = 7.89;
    EXPECT_DOUBLE_EQ((double)script["table"]["o"][3], 7.89);

    script["table"]["o"][4] = "abc";
    EXPECT_EQ((std::string)script["table"]["o"][4], "abc");
}

TEST_F(SunScriptTest, LuaFunctions) {
    int result = script["add"](1, 2);
    EXPECT_EQ(result, 3);

    int add;
    int multiply;
    script["addAndMultiply"](4, 5).assign(add, multiply);
    EXPECT_EQ(add, 9);
    EXPECT_EQ(multiply, 20);
}

TEST_F(SunScriptTest, RunLua) {
    script.run("z = 5");
    EXPECT_EQ((int)script["z"], 5);

    script.run("z = z + 2");
    EXPECT_EQ((int)script["z"], 7);

    script("z = (z * 2) - 1");
    EXPECT_EQ((int)script["z"], 13);
}

int divide(int a, int b) {
    return a / b;
}

int add(int a, int b, int c) {
    return a + b + c;
}

int zaz = 0;

void sum(int a, int b) {
    zaz = a + b;
}

TEST_F(SunScriptTest, CFunctions) {
    // Test Lambda
    auto cat = [](const char *a, const char *b) -> char * {
        char *result = (char *)malloc(strlen(a) + strlen(b) + 1);
        strcpy(result, a);
        strcat(result, b);
        return result;
    };
    std::function<const char *(const char *, const char *)> _cat = cat;
    script.registerFunction("cat", _cat);
    std::string x = (std::string)script["cat"]("1 + 2", " = 3");
    EXPECT_EQ(x, "1 + 2 = 3");

    // Test std::function
    std::function<int(int, int, int)> _add = add;
    script.registerFunction("add3", _add);
    script("abs = add3(1, 2, 3)");
    int y = script["abs"];
    EXPECT_EQ(y, 6);

    script["functions"].newTable();

    // Test C Function
    script.registerFunction(script["functions"]["divide"], &divide);
    int z = script["functions"]["divide"](30, 5);
    EXPECT_EQ(z, 6);

    // Test Void Function
    //script.registerFunction(script["functions"]["sum"], &sum);
    //script["functions"]["sum"](5, 7);
    //EXPECT_EQ(zaz, 12);
} 
