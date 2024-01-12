cmake_minimum_required(VERSION 3.5)
project(cmod_test)

# set(CMAKE_C_STANDARD 99)
# set(CMAKE_CXX_STANDARD 11)

# needs -g to debug.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

# TODO1 fix these paths. Or use built libs?
set(CBOT   "C:/Dev/repos/C/c_bag_of_tricks")


include_directories(
    source/common_module
    source/cli_module
    source/exec_module
    source/io_module
    source/hal_module
    ${CBOT}/pnut
    )
    
# add_compile_definitions(HAVE_LIST=1)

# Source files.
add_executable(cmod_test
    source/run.c
    source/common_module/private/common_debug.c
    source/common_module/private/common_module.c
    source/exec_module/private/exec_module.c
    source/cli_module/private/cli_process.c
    source/io_module/private/io_module.c
    source/io_module/private/io_digital.c
    source/io_module/private/io_analog.c
    # source/hal_module/private/hal_board.c
    test/test_main.cpp
    test/test_cli.cpp
    test/test_exec.cpp
    test/test_io.cpp
    test/hal_board_mock.c
    ${CBOT}/pnut/pnut.cpp
    )
