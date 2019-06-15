
# Project to enforce C99 compliance.
TEMPLATE = app
CONFIG += console strict_c c99
CONFIG -= app_bundle qt c11 gui c++11

# Keep it honest - treat warnings as errors.
QMAKE_CFLAGS += -Werror

SRC_PATH = "./source"

INCLUDEPATH += \
    $$SRC_PATH/common_module \
    $$SRC_PATH/cli_module \
    $$SRC_PATH/exec_module \
    $$SRC_PATH/io_module \
    $$SRC_PATH/hal_module

SOURCES += \
    $$SRC_PATH/main.c \
    $$SRC_PATH/common_module/private/common_debug.c \
    $$SRC_PATH/common_module/private/common_module.c \
    $$SRC_PATH/exec_module/private/exec_loop.c \
    $$SRC_PATH/cli_module/private/cli_process.c \
    $$SRC_PATH/io_module/private/io_digital.c \
    $$SRC_PATH/io_module/private/io_analog.c \
    $$SRC_PATH/hal_module/private/hal_board.c

HEADERS += \
    $$SRC_PATH/common_module/common_module.h \
    $$SRC_PATH/cli_module/cli_module.h \
    $$SRC_PATH/exec_module/exec_module.h \
    $$SRC_PATH/io_module/io_module.h \
    $$SRC_PATH/hal_module/hal_module.h \
    $$SRC_PATH/common_module/private/common_private.h
