# cmake needs this line
cmake_minimum_required(VERSION 3.5)

# Define project name
project(basler_rdbd)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



add_subdirectory(camera)
add_subdirectory(src)
# add_subdirectory(ToF_camera)


