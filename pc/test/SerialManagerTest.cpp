#include <gtest/gtest.h>
#include "SerialManager.h"
#include "SerialDevice.h"

class SerialManagerTest : public ::testing::Test {
protected:
    TSerialDevice _device;
    SerialManager _manager{_device};
};

TEST_F(SerialManagerTest, InitSuccess) {
    _device.setFailState(false);
    EXPECT_TRUE(_manager.init());
}

TEST_F(SerialManagerTest, InitFailsWhenOpenFails) {
    _device.setFailState(true);
    EXPECT_FALSE(_manager.init());
}