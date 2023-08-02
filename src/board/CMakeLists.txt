add_library(board INTERFACE)

if(NOT ENABLE_CROSS_COMPILING)
  add_subdirectory(sandbox)
else()
  add_subdirectory(stm32f1xx)
endif()
