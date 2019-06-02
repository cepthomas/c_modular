# c-modular

## Overview
This is a formalization of several techniques I have used in the past when implementing embedded C code.
While you have to debug the final package on the target in real time, that is a pain to do for the more
mundane and algorithmic stuff. To make life easier, it is necessary to separate out the hardware and time
dependent content from the rest of the application. When they are isolated they can be replaced by components
more tuned to debugging and testing. While this can be done with all sorts of FOSS I find the majority to be
too heavy or unecessarily complicated. I just want a simple way to stub IO so end up with a home-brew that
is used in conjunction with my trusty unit tester [pnut](https://github.com/cepthomas/pnut).

## Modules
In other languages, interfaces or abstract classes are very handy for defining the boundaries that can be 
swapped. However C does not support these higher level constructs. There are several efforts to impart the
notion at compile time - noble but again too complicated. This uses a file-based approach to interfaces
aka a module system (there are other ways to do modules too). It requires a certain amount of discipline
and adherence to convention but we're all pros here, right?

A module is simply a subdir that follows this pattern:
```
source
\---example_module
    |   example_module.h
    |   
    \---private
            example_impl.c
            example_internal.c
```
Where:
- `example_module.h` contains only the minimum public needed by a consumer of this module.
- `example_impl.c` and `example_internal.c` contain all the code required to do the work.

There are some other conventions:
All module public functions are of the form:
``` C
int example_myFunc1(args);
void example_myFunc2(args);
```
Everything not public is static and looks like:
``` C
static bool s_myStatus;
static void s_myPrivateFunc(args);
```

So from an external POV this barebones example project looks like:
```
source
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
    hal_sim.c
    hal_sim.h
    test_all.cpp
    main.cpp
    pnut.h
```
Where:
- `hal_sim.c` is the simulation implementation of the hal_module from above, in addition to other functionality
  to support simulation.
- `hal_sim.h` for other shared/common stuff.
- `test_all.cpp` contains the actual test suites.
- `main.cpp` is the entry point and test executor.
- `pnut.h` is the unit test framework.

## Building
There are two bodies of code here, the application source, and the test executable.
The former is a pure C99 application which should compile anywhere, even minimal embedded systems. There is a QMake/mingw project
included to build it. The test code is a C++ application so we can use higher level constructs 
to create test code that executes the pure C application. There is also a QMake/mingw project
for that.

## License
https://github.com/cepthomas/c-modular/blob/master/LICENSE
