#include <gtest/gtest.h>

#include "config.h"

TEST(ConfigTest, ProjectName) { ASSERT_EQ("stm32-cmake-template", project_name); }