add_executable(stm32_app main.cpp)
target_link_libraries(stm32_app PRIVATE stm32_project_options stm32_project_warnings)

add_subdirectory(board)
target_link_libraries(stm32_app PRIVATE board)
