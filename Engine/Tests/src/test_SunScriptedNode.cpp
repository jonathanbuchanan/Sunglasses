#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Sunglasses/Sunglasses.hpp>

struct SunScriptedNodeTest : ::testing::Test {
    SunScriptedNode node;
    SunScriptedNodeTest() {
        node.loadFile("src/test_SunScriptedNode_0.lua");
        node.loadFile("src/test_SunScriptedNode_1.lua");
    }

    ~SunScriptedNodeTest() {

    }
};

TEST_F(SunScriptedNodeTest, LuaVariables) {
    int x = node.getVariable("x");
    EXPECT_EQ(x, 2);

    double pi = node.getVariable("pi");
    EXPECT_DOUBLE_EQ(pi, 3.14);

    bool yes = node.getVariable("yes");
    EXPECT_EQ(yes, true);

    bool no = node.getVariable("no");
    EXPECT_EQ(no, false);

    std::string str = node.getVariable("str");
    EXPECT_EQ(str, "Hello, World!");

    int a = node.getVariable("table")["a"];
    EXPECT_EQ(a, 7);

    double b = node.getVariable("table")["b"];
    EXPECT_DOUBLE_EQ(b, 1.23);

    bool c = node.getVariable("table")["c"];
    EXPECT_EQ(c, true);

    bool d = node.getVariable("table")["d"];
    EXPECT_EQ(d, false);

    std::string e = node.getVariable("table")["e"];
    EXPECT_EQ(e, "Test");
}

TEST_F(SunScriptedNodeTest, LuaFunctions) {
    int result = node.getFunction("add")(1, 2);
    EXPECT_EQ(result, 3);
}

TEST_F(SunScriptedNodeTest, RunLua) {
    node.run("z = 5");
    EXPECT_EQ((int)node["z"], 5);

    node.run("z = z + 2");
    EXPECT_EQ((int)node["z"], 7);

    node("z = (z * 2) - 1");
    EXPECT_EQ((int)node["z"], 13);
}

int divide(int a, int b) {
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
}
