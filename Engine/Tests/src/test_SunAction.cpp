#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Sunglasses/Sunglasses.hpp>

struct SunActionTest : ::testing::Test {
    SunAction action;
    SunActionTest() {
        std::string actionString = "action";
        int *_int = new int(7);
        float *_float = new float(3.14159);
        std::string *_string = new std::string("Hello, World!");
        std::map<std::string, void *> parameters = {{"int", _int}, {"float", _float}, {"string", _string}};
        bool recursive = false;

        action = SunAction(actionString, parameters, recursive);
    }

    ~SunActionTest() {

    }
};

TEST_F(SunActionTest, action) {
    EXPECT_EQ(action.getAction(), "action");
}

TEST_F(SunActionTest, parameters) {
    EXPECT_EQ(*(int *)action.getParameter("int"), 7);
    float _float = *(float *)action.getParameter("float");
    EXPECT_FLOAT_EQ(_float, 3.14159);
    EXPECT_EQ(*(std::string *)action.getParameter("string"), "Hello, World!");
}

TEST_F(SunActionTest, recursive) {
    EXPECT_EQ(false, action.getRecursive());
}

class MockSunBase : public SunBase {
public:
    MOCK_METHOD0(test, void());
};

struct SunLambdaActionTest : ::testing::Test {
    MockSunBase base;
    SunLambdaAction action;
    SunLambdaActionTest() {
        auto function = [](SunBase *base) {
            ((MockSunBase *)base)->test();
        };
        action = SunLambdaAction(function);
        EXPECT_CALL(base, test()).Times(3);
    }

    ~SunLambdaActionTest() {

    }
};

TEST_F(SunLambdaActionTest, run) {
    action.run(&base);
    action.run(&base);
    action.run(&base);
}
