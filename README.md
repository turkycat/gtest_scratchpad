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

##### Building Production Code

Navigate to the root directory of this repository in a terminal window and run the following commands.

```
mkdir build
cd build
cmake ..
make
```