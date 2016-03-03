#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Sunglasses/Sunglasses.hpp>

struct SunScriptTest : ::testing::Test {
    SunScript script;
    SunScriptTest() {
        script.loadFile("src/test_SunScript_0.lua");
        script.loadFile("src/test_SunScript_1.lua");
    }

    ~SunScriptTest() {

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

    SunLuaValue e_ = script.getVariable("table");
    EXPECT_EQ((std::string)e_["e"], "Test");

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

    script["o"].newTable();

    script["o"]["a"] = -3;
    EXPECT_EQ((int)script["o"]["a"], -3);

    script["o"]["b"] = true;
    EXPECT_EQ((bool)script["o"]["b"], true);

    script["o"]["c"] = 7.89;
    EXPECT_DOUBLE_EQ((double)script["o"]["c"], 7.89);

    script["o"]["z"] = "abc";
    EXPECT_EQ((std::string)script["o"]["z"], "abc");
}

TEST_F(SunScriptTest, LuaFunctions) {
    int result = script["add"](1, 2);
    EXPECT_EQ(result, 3);

    int add;
    int multiply;
    //std::tie(add, multiply) = script["addAndMultiply"](4, 5).tie();
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

/*int divide(int a, int b) {
    return a / b;
}

TEST_F(SunScriptedNodeTest, CFunctions) {
    // Test Lambda
    auto multiply = [](int a, int b) -> int {
        return a * b;
    };
    node.registerFunction("multiply", multiply);
    int x = node["multiply"](7, 6);
    EXPECT_EQ(x, 42);

    // Test std::function
    std::function<int(int, int)> subtract = std::function<int(int, int)>([](int a, int b) -> int {
        return a - b;
    });
    node.registerFunction("subtract", subtract);
    int y = node["subtract"](10, 3);
    EXPECT_EQ(y, 7);

    // Test C Function
    node.registerFunction("divide", &divide);
    int z = node["divide"](30, 5);
    EXPECT_EQ(z, 6);
}

struct TestClass {
    int x;
    TestClass(int _x) { x = _x; }

    void add(int a) {
        x = x + a;
    }

    void multiply(int a) {
        x = x * a;
    }
};

TEST_F(SunScriptedNodeTest, Classes) {
    node.registerClass<TestClass, int>("TestClass", "multiply", &TestClass::multiply, "add", &TestClass::add, "x", &TestClass::x);
    node("test = TestClass.new(5)");
    node("z = test:x()");
    int z = node["z"];
    EXPECT_EQ(z, 5);

    node("test:multiply(2)");
    node("z = test:x()");
    z = node["z"];
    EXPECT_EQ(z, 10);

    node("test:add(4)");
    node("z = test:x()");
    z = node["z"];
    EXPECT_EQ(z, 14);
}

TEST_F(SunScriptedNodeTest, Objects) {
    TestClass test(6);
    node.registerObject("test", test, "add", &TestClass::add, "multiply", &TestClass::multiply, "x", &TestClass::x);
    EXPECT_EQ((int)node["test"]["x"](), 6);
    EXPECT_EQ(test.x, 6);

    node("test.add(4)");
    EXPECT_EQ((int)node["test"]["x"](), 10);
    EXPECT_EQ(test.x, 10);

    test.multiply(3);
    EXPECT_EQ((int)node["test"]["x"](), 30);
    EXPECT_EQ(test.x, 30);
}*/
