# Author: Daniel Raudschus / Michael Bunk
# Date: 26.04.2014

# Show compilation flags to report all warnings
set(CMAKE_C_FLAGS “-Wall -g“)

# Adds all files that end with .cpp to SRCS
file(GLOB SRCS *.cpp)

# Define Executable
add_executable(spacerace ${SRCS})