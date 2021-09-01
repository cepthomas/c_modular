# c_modular

## Overview
This is a formalization of several techniques I have used in the past when implementing embedded C code.
While you have to debug the final package on the target in real time, that is a pain to do for the more
mundane and algorithmic stuff. To make life easier, it is necessary to separate out the hardware and time
dependent content from the rest of the application. When they are isolated they can be replaced by components
more tuned to debugging and testing. While this can be done with all sorts of FOSS I find the majority to be
too heavy or unecessarily complicated. I just want a simple way to stub IO so ended up with a home-brew that
is used in conjunction with my trusty unit tester [pnut](https://github.com/cepthomas/c_bag_of_tricks).

## Modules
In other languages, interfaces or abstract classes are very handy for defining the boundaries that can be 
swapped. However C does not support these higher level constructs. There are several efforts to impart the
notion at compile time - noble but again too complicated. This uses a file-based approach to interfaces
aka a module system (there are other ways to do modules too). It requires a certain amount of discipline
and adherence to convention but we're all pros here, right?

A module is simply a subdir that follows this pattern:
```
source
\---abc_module
    |   abc_module.h
    |   
    \---private
            abc_impl.c
            abc_internal.c
```
Where:
- `abc_module.h` contains only the minimum public needed by a consumer of this module.
- `abc_impl.c` and `abc_internal.c` contain all the code required to do the work.

There are some other conventions:
All module public functions are of the form:
``` C
int abc_myFunc1(args);
void abc_myFunc2(args);
```
Everything not public is private/static and looks like:
``` C
static bool p_myStatus;
static void p_myPrivateFunc(args);
```

## Example
A somewhat brain-dead example of a hypothetical embedded C project is provided.
The application source looks like this:
```
source
main.c
+---cli_module
|   |   cli_module.h
|   \---private
+---common_module
|   |   common_defs.h
|   |   common_module.h
|   \---private
+---exec_module
|   |   exec_module.h
|   \---private
+---hal_module
|   |   hal_module.h
|   \---private
\---io_module
    |   io_module.h
    \---private
```
Of particular note is the hal_module - the hardware abstraction layer. In order to test the rest
of the application it is only necessary to replace the implementation of that one module.

The test code structure then looks like:
```
test
    hal_board_mock.c
    hal_board_mock.h
    test_xxx.cpp
    main.cpp
    pnut.h
```
Where:
- `hal_board_mock.c` and `hal_board_mock.h` contain:
    - the simulation implementation of the hal_module. Note that it would make more sense to use something like [fff](https://github.com/meekrosoft/fff).
    - the hooks between the hal_module and the test suites.
- `test_xxx.cpp` contains the test suites.
- `main.cpp` is the entry point and test executor.
- `pnut.h` is the unit test framework.

## Build
There are two bodies of code here, the application library, and a test executable.

The former is pure C99 which should compile anywhere, even for minimal embedded systems.

If you want to use the latter, it requires [c_bag_of_tricks](https://github.com/cepthomas/c_bag_of_tricks)
at the same level as this project. Maybe I'll make it a submodule some time.

Also a VS Code workspace using mingw and CMake is supplied.
