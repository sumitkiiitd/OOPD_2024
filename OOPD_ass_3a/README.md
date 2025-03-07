# Railway System Project

This project simulates a railway system, written in C++ and utilizing different build configurations (debug and optimized). The `Makefile` provided compiles the source code in both debug and optimized modes.

## Requirements

- **g++**: Ensure that `g++` is installed on your system. This project requires C++17 support.
  
## Files

- **Test.cpp**: Main source file for the railway system project.
- **Makefile**: Automates the build process with configurations for debug and optimized builds.

## Makefile Targets

The `Makefile` has the following targets:

- **all**: Builds both `debug` and `optimized` versions.
- **debug**: Compiles `Test.cpp` with debug symbols for easier debugging.
- **optimized**: Compiles `Test.cpp` with optimizations enabled for better performance.
- **clean**: Removes all compiled binaries.

## Build Instructions

1. To compile both `debug` and `optimized` binaries, run:
   ```bash
   make
2. To compile only the debug binary, run:
    ```bash
    make debug
3. To compile only the optimized binary, run:
    ```bash
    make optimized
4. To clean up and remove the binaries, run:
    ```bash
    make clean
    