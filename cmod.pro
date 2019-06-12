
# Project to enforce C99 compliance.
TEMPLATE = app
CONFIG += console strict_c c99
CONFIG -= app_bundle qt c11 gui c++11

# Keep it honest - treat warnings as errors.
QMAKE_CFLAGS += -Werror


INCLUDEPATH += \
    source/common_module \
    source/cli_module \
    source/exec_module \
    source/io_module \
    source/hal_module

SOURCES += \
    source/main.c \
    source/common_module/private/common_debug.c \
    source/common_module/private/common_module.c \
    source/exec_module/private/exec_loop.c \
    source/cli_module/private/cli_process.c \
    source/io_module/private/io_digital.c \
    source/io_module/private/io_analog.c \
    source/hal_module/private/hal_board.c

HEADERS += \
    source/common_module/common_module.h \
    source/cli_module/cli_module.h \
    source/exec_module/exec_module.h \
    source/io_module/io_module.h \
    source/hal_module/hal_module.h \
    source/common_module/private/common_private.h
