cmake_minimum_required(VERSION 3.16)
project(basler_rgbd)

list(APPEND CMAKE_PREFIX_PATH "/opt/MVS/lib/64/")

set(_SRCS
    # bfvs.cpp
    test.cpp
    # tcp_client.cpp
    # utility.cpp
)
# set(_HDRS
#     bfvs_messaging.h
#     # tcp_client.hpp
# )

find_library(CAMERA_LIB MvCameraControl REQUIRED)
find_package(OpenCV REQUIRED)


add_executable(${PROJECT_NAME} 
    ${_SRCS} 
    )


target_include_directories(${PROJECT_NAME} 
    PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    /opt/MVS/include
    # ${CMAKE_SOURCE_DIR}/YoloNet
    ${CMAKE_SOURCE_DIR}/camera
    )

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    stdc++fs
    pthread
    ${OpenCV_LIBS}
    camera
    # YoloNet    
)