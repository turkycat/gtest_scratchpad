#!/bin/bash

# check if we have any arguments
while [ $# -ne 0 ]
do
  case "$1" in
    --clean) clean=true
      ;;
    -c) clean=true
      ;;
    --test) buildtests=true
      ;;
    -t) buildtests=true
      ;;
    *)
    ;;
  esac
  shift
done

if [ "$clean" == true ]; then
  echo "cleaning build directory"
  rm -rf build
  exit 0;
fi

#check if the build directory exists
if [ ! -d "build" ]; then
  echo "Creating build/ directory"
  mkdir build
fi

cd build

if [ "$buildtests" == true ]; then
  cmake -Dbuild_tests=true ..
else
  cmake ..
fi

make

if [ "$buildtests" == true ]; then
  ./runtests
  ./integration
fi