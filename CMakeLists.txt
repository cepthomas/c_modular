# Build the module with its unit tests.

cmake_minimum_required(VERSION 3.5)
project(cmod_test)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")


include_directories(
    source_code/common_module
    source_code/cli_module
    source_code/exec_module
    source_code/io_module
    source_code/hal_module
    )
    
# Source files.
add_executable(cmod_test
    source_code/run.c
    source_code/common_module/private/common_debug.c
    source_code/common_module/private/common_module.c
    source_code/exec_module/private/exec_module.c
    source_code/cli_module/private/cli_process.c
    source_code/io_module/private/io_module.c
    source_code/io_module/private/io_digital.c
    source_code/io_module/private/io_analog.c
    test_code/main.c
    test_code/hal_board_mock.c
    )
