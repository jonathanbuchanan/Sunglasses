// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sunglasses/Sunglasses.hpp>

using namespace sunglasses;

class MockResource : public Resource {
public:
    MOCK_METHOD0(init, void());
};

struct ResourceManagerTest : ::testing::Test {
    ResourceManager *manager;
    MockResource *resource;

    ResourceManagerTest() {
        manager = new ResourceManager();
        resource = new MockResource();
    }

    ~ResourceManagerTest() {
        delete manager;
    }
};

TEST_F(ResourceManagerTest, Resources) {
    EXPECT_CALL((*resource), init()).Times(1);
    EXPECT_EQ(manager->addResource("res0", resource), 0);

    EXPECT_EQ(manager->getResource("res0"), resource);
    EXPECT_EQ((*manager)["res0"], resource);

    EXPECT_EQ(manager->addResource("res0", resource), -1);

    EXPECT_EQ(manager->removeResource("res0"), 0);

    EXPECT_EQ(manager->getResource("res0"), nullptr);
    EXPECT_EQ((*manager)["res0"], nullptr);

    EXPECT_EQ(manager->removeResource("res0"), -1);
}
