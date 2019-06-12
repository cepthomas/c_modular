
TEMPLATE = app
CONFIG += console warn_off
CONFIG -= app_bundle qt


INCLUDEPATH += \
    source/common_module \
    source/cli_module \
    source/exec_module \
    source/io_module \
    source/hal_module

### Code being tested.
SOURCES += \
    source/common_module/private/common_debug.c \
    source/common_module/private/common_module.c \
    source/exec_module/private/exec_loop.c \
    source/cli_module/private/cli_process.c \
    source/io_module/private/io_digital.c \
    source/io_module/private/io_analog.c

HEADERS += \
    source/common_module/common_module.h \
    source/cli_module/cli_module.h \
    source/exec_module/exec_module.h \
    source/io_module/io_module.h \
    source/hal_module/hal_module.h


### Test code.
SOURCES += \
    test/main.cpp \
    test/test_exec.cpp \
    test/test_io.cpp \
    test/test_cli.cpp \
    test/hal_sim.c \
    test/pnut.cpp

HEADERS += \
    test/hal_sim.h \
    test/pnut.h
