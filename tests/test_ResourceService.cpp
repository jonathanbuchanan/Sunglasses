// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sunglasses/Sunglasses.hpp>

using namespace sunglasses;

struct ResourceServiceTest : ::testing::Test {
    ResourceService *service;
    ResourceManager *manager;

    ResourceServiceTest() {
        service = new ResourceService();
        manager = new ResourceManager();
    }

    ~ResourceServiceTest() {

    }
};

TEST_F(ResourceServiceTest, ResourceManagers) {
    EXPECT_EQ(service->addResourceManager("manager0", manager), 0);

    EXPECT_EQ(service->getResourceManager("manager0"), manager);
    EXPECT_EQ((*service)["manager0"], manager);

    EXPECT_EQ(service->addResourceManager("manager0", manager), -1);

    EXPECT_EQ(service->removeResourceManager("manager0"), 0);

    EXPECT_EQ((*service)["manager0"], nullptr);
    EXPECT_EQ(service->getResourceManager("manager0"), nullptr);

    EXPECT_EQ(service->removeResourceManager("manager0"), -1);
}
