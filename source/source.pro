
TEMPLATE = app

# Enforce C99 application.
CONFIG += console strict_c c99
CONFIG -= app_bundle qt c11 gui c++11


INCLUDEPATH += \
    common_module \
    cli_module \
    exec_module \
    io_module \
    hal_module

SOURCES += \
    common_module/private/common_debug.c \
    common_module/private/common_module.c \
    exec_module/private/exec_main.c \
    exec_module/private/exec_loop.c \
    cli_module/private/cli_process.c \
    io_module/private/io_digital.c \
    io_module/private/io_analog.c \
    hal_module/private/hal_board.c

HEADERS += \
    common_module/common_module.h \
    cli_module/cli_module.h \
    exec_module/exec_module.h \
    io_module/io_module.h \
    hal_module/hal_module.h


HEADERS += \
    common_module/private/common_private.h


# Always good practice - treat warnings as errors. Clean up yo messes.
QMAKE_CFLAGS += -Werror
