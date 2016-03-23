#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Sunglasses/Sunglasses.hpp>

struct SunResourceServiceTest : ::testing::Test {
    SunResourceService *service;
    SunResourceManager *manager;

    SunResourceServiceTest() {
        service = new SunResourceService();
        manager = new SunResourceManager();
    }

    ~SunResourceServiceTest() {

    }
};

TEST_F(SunResourceServiceTest, ResourceManagers) {
    EXPECT_EQ(service->addResourceManager("manager0", manager), 0);

    EXPECT_EQ(service->getResourceManager("manager0"), manager);
    EXPECT_EQ((*service)["manager0"], manager);

    EXPECT_EQ(service->addResourceManager("manager0", manager), -1);

    EXPECT_EQ(service->removeResourceManager("manager0"), 0);

    EXPECT_EQ((*service)["manager0"], nullptr);

    EXPECT_EQ(service->removeResourceManager("manager0"), -1);
}
