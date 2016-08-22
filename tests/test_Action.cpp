// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sunglasses/Sunglasses.hpp>

using namespace sunglasses;

struct ActionTest : ::testing::Test {
    Action action;
    ActionTest() {
        std::string actionString = "action";
        int *_int = new int(7);
        float *_float = new float(3.14159);
        double *_double = new double(2.7);
        std::string *_string = new std::string("Hello, World!");
        std::map<std::string, void *> parameters = {{"int", _int}, {"float", _float}, {"double", _double}, {"string", _string}};
        bool recursive = false;

        action = Action(actionString, parameters, recursive);
    }

    ~ActionTest() {

    }
};

TEST_F(ActionTest, action) {
    EXPECT_EQ(action.getAction(), "action");
}

TEST_F(ActionTest, parameters) {
    EXPECT_EQ(*(int *)action.getParameter("int"), 7);
    EXPECT_FLOAT_EQ(action.getParameter<float>("float"), 3.14159);
    double *_double = action.getParameterPointer<double>("double");
    EXPECT_DOUBLE_EQ(*_double, 2.7);
    EXPECT_EQ(action.getParameter<std::string>("string"), "Hello, World!");
}

TEST_F(ActionTest, recursive) {
    EXPECT_EQ(action.getRecursive(), false);
}
