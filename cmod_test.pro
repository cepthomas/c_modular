
TEMPLATE = app
CONFIG += console warn_off
CONFIG -= app_bundle qt


SRC_PATH = "./source"
TEST_PATH = "./test"
# This may break other users. Env var?
CBOT_PATH = "../c-bag-of-tricks/source"


INCLUDEPATH += \
    $$SRC_PATH/common_module \
    $$SRC_PATH/cli_module \
    $$SRC_PATH/exec_module \
    $$SRC_PATH/io_module \
    $$SRC_PATH/hal_module \
    $$CBOT_PATH

### Code being tested.
SOURCES += \
    $$SRC_PATH/common_module/private/common_debug.c \
    $$SRC_PATH/common_module/private/common_module.c \
    $$SRC_PATH/exec_module/private/exec_module.c \
    $$SRC_PATH/cli_module/private/cli_process.c \
    $$SRC_PATH/io_module/private/io_module.c \
    $$SRC_PATH/io_module/private/io_digital.c \
    $$SRC_PATH/io_module/private/io_analog.c

HEADERS += \
    $$SRC_PATH/common_module/common_module.h \
    $$SRC_PATH/cli_module/cli_module.h \
    $$SRC_PATH/exec_module/exec_module.h \
    $$SRC_PATH/io_module/io_module.h \
    $$SRC_PATH/hal_module/hal_module.h


### Test code.
SOURCES += \
    $$TEST_PATH/main.cpp \
    $$TEST_PATH/test_exec.cpp \
    $$TEST_PATH/test_io.cpp \
    $$TEST_PATH/test_cli.cpp \
    $$TEST_PATH/hal_sim.c \
    $$CBOT_PATH/pnut.cpp

HEADERS += \
    $$TEST_PATH/hal_sim.h \
    $$CBOT_PATH/pnut.h
