find_package(GMock REQUIRED)
include(GoogleTest)

set(SOURCE config_test.cpp)

add_executable(stm32_test ${SOURCE})
target_link_libraries(stm32_test PRIVATE ${GMOCK_LIBRARIES})
gtest_discover_tests(stm32_test)
