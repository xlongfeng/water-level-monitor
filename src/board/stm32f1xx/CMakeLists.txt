set(STM32_CUBE_F1_PATH $ENV{STM32_CUBE_F1_SRC})

set(HAL_COMP_LIST
    CORTEX
    GPIO
    RCC
    UART)
set(CMSIS_COMP_LIST "")

list(APPEND CMSIS_COMP_LIST STM32F1)
list(APPEND HAL_COMP_LIST STM32F1)

find_package(
  CMSIS
  COMPONENTS "${CMSIS_COMP_LIST}"
  REQUIRED)
find_package(
  HAL
  COMPONENTS "${HAL_COMP_LIST}"
  REQUIRED)

target_link_libraries(
  board
  INTERFACE CMSIS::STM32::F103C6
            HAL::STM32::F1::CORTEX
            HAL::STM32::F1::GPIO
            HAL::STM32::F1::RCC
            HAL::STM32::F1::UART
            STM32::Nano)

target_include_directories(board INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(board INTERFACE syscalls.cpp)
