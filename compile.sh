#!/bin/bash

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Navigate to the build directory
cd build

# Run CMake and make
cmake ..
make

# Move the executable to the root directory
if [ -f "GameOfLife" ]; then
    mv GameOfLife ..
    echo "Compilation successful! Executable moved to the project root."
else
    echo "Compilation failed. Please check for errors."
fi
