
TEMPLATE = app
CONFIG += console c++11 #strict_c c99
CONFIG -= app_bundle qt gui


# Source Under Test
SUT_PATH = "../source"

BASE_DIR = $$shell_path($$PWD/..)

INCLUDEPATH += \
    ./ \
    $$SUT_PATH/common_module \
    $$SUT_PATH/cli_module \
    $$SUT_PATH/exec_module \
    $$SUT_PATH/io_module \
    $$SUT_PATH/hal_module

SOURCES += \
    $$SUT_PATH/common_module/private/common_debug.c \
    $$SUT_PATH/common_module/private/common_module.c \
    $$SUT_PATH/exec_module/private/exec_loop.c \
    $$SUT_PATH/cli_module/private/cli_process.c \
    $$SUT_PATH/io_module/private/io_digital.c \
    $$SUT_PATH/io_module/private/io_analog.c

HEADERS += \
    $$SUT_PATH/common_module/common_module.h \
    $$SUT_PATH/cli_module/cli_module.h \
    $$SUT_PATH/exec_module/exec_module.h \
    $$SUT_PATH/io_module/io_module.h \
    $$SUT_PATH/hal_module/hal_module.h


SOURCES += \
    hal_sim.c \
    main.cpp \
    test_exec.cpp \
    test_io.cpp \
    test_cli.cpp


HEADERS += \
    hal_sim.h \
    pnut.h
