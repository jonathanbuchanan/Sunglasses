#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Sunglasses/Sunglasses.hpp>

class MockSunResource : public SunResource {
public:
    MOCK_METHOD0(init, void());
};

struct SunResourceManagerTest : ::testing::Test {
    SunResourceManager *manager;
    MockSunResource *resource;

    SunResourceManagerTest() {
        manager = new SunResourceManager();
        resource = new MockSunResource();
    }

    ~SunResourceManagerTest() {

    }
};

TEST_F(SunResourceManagerTest, Resources) {
    EXPECT_EQ(manager->addResource("res0", resource), 0);

    EXPECT_EQ(manager->getResource("res0"), resource);
    EXPECT_EQ((*manager)["res0"], resource);

    EXPECT_EQ(manager->addResource("res0", resource), -1);

    EXPECT_EQ(manager->removeResource("res0"), 0);

    EXPECT_EQ(manager->getResource("res0"), nullptr);
    EXPECT_EQ((*manager)["res0"], nullptr);

    EXPECT_EQ(manager->removeResource("res0"), -1);
}
