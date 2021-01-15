cmake_minimum_required(VERSION 3.5)
project(cmod_test)

# set(CMAKE_C_STANDARD 99)
# set(CMAKE_CXX_STANDARD 11)

# Source files.
include_directories(
    source/common_module
    source/cli_module
    source/exec_module
    source/io_module
    source/hal_module
    ../c-bag-of-tricks/source
    )
# add_compile_definitions(HAVE_LIST=1)

add_executable(cmod_test
    source/main.c
    source/common_module/private/common_debug.c
    source/common_module/private/common_module.c
    source/exec_module/private/exec_module.c
    source/cli_module/private/cli_process.c
    source/io_module/private/io_module.c
    source/io_module/private/io_digital.c
    source/io_module/private/io_analog.c
    source/hal_module/private/hal_board.c
    test/hal_sim.c
    test/hal_sim.h
    test/test_cli.cpp
    test/test_exec.cpp
    test/test_io.cpp
    )

# needs -g!
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror -Wno-deprecated-declarations") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror")
# set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")
