// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Sunglasses/Sunglasses.hpp>

struct SunCLOptionTest : ::testing::Test {
    std::vector<SunCLOption> options;
    int argc0;
    char **argv0;

    int argc1;
    char **argv1;

    int argc2;
    char **argv2;

    int var = 0;

    SunCLOptionTest() {
        SunCLOption option0 = SunCLOption("i", "increment", "increments a variable", [this](int argc, char **argv, int i) -> void {
            var += 1;
        });
        options.push_back(option0);

        SunCLOption option1 = SunCLOption("d", "decrease", "decreases a variable by a certain amount", [this](int argc, char **argv, int i) -> void {
            char *arg = getArgument(argc, argv, i);
            var -= stoi(std::string(arg), nullptr);
        });
        options.push_back(option1);


        argv0 = (char **)malloc(2 * sizeof(char *));
        argv0[0] = (char *)malloc(strlen("./command") * sizeof(char *));
        strcpy(argv0[0], "./command");
        argv0[1] = (char *)malloc(strlen("-i") * sizeof(char *));
        strcpy(argv0[1], "-i");
        argc0 = 2;


        argv1 = (char **)malloc(2 * sizeof(char *));
        argv1[0] = (char *)malloc(strlen("./command") * sizeof(char *));
        strcpy(argv1[0], "./command");
        argv1[1] = (char *)malloc(strlen("-ii") * sizeof(char *));
        strcpy(argv1[1], "-ii");
        argc1 = 2;


        argv2 = (char **)malloc(3 * sizeof(char *));
        argv2[0] = (char *)malloc(strlen("./command") * sizeof(char *));
        strcpy(argv2[0], "./command");
        argv2[1] = (char *)malloc(strlen("-d") * sizeof(char *));
        strcpy(argv2[1], "-d");
        argv2[2] = (char *)malloc(strlen("50") * sizeof(char *));
        strcpy(argv2[2], "50");
        argc2 = 3;
    }

    ~SunCLOptionTest() {

    }
};

TEST_F(SunCLOptionTest, initialization) {
    EXPECT_EQ(options[0].shortName, "i");
    EXPECT_EQ(options[0].longName, "increment");
    EXPECT_EQ(options[0].description, "increments a variable");
}

TEST_F(SunCLOptionTest, parsing) {
    parseOptions(argc0, argv0, options);
    EXPECT_EQ(var, 1);

    parseOptions(argc1, argv1, options);
    EXPECT_EQ(var, 2); // Don't call an option twice

    parseOptions(argc2, argv2, options);
    EXPECT_EQ(var, -48);
}
