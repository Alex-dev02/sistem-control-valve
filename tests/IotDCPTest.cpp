#include <gtest/gtest.h>

#include "../networking/IotDCP/IotDCP.hpp"

TEST(IotDCPTest, CheckVersion) {
    IotDCP dcp;
    EXPECT_EQ("0.1", dcp.GetVersion());
}
