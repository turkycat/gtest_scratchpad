# gtest_scratchpad

### Overview

This repository is intended to show off the basic integration of GoogleTest and GoogleMock. There is some "production code" in the root of this repository, as well as some "libraries" in `/src` and headers in `/include/`.

GoogleTest will be integrated with basic use cases, with various branches showing off integration strategies.

### How To Build

##### Prerequisites

You must have CMake and Make installed. Run the following command once per machine.

```
sudo apt-get install cmake make
```

### Building

Simply execute the build script `build.sh` in the root directory.

You may pass in `-c` or `--clean` to clear all build outputs.

You may pass in `-t` or `--test` to build and run all tests automatically.

##### Manually Building Production Code

Navigate to the root directory of this repository in a terminal window and run the following commands.

```
mkdir build
cd build
cmake ..
make
```

##### Manually Building Tests

In order to build the unit tests in addition to the test code, we will modify only one command of our steps above.

```
mkdir build
cd build
cmake -Dbuild_tests=true ..
make
```