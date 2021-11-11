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


#=============================================

set(BaslerBlaze_ROOT_DIR "/opt/Basler_blaze")
set(module_path ${BaslerBlaze_ROOT_DIR}/lib/cmake)
list(APPEND CMAKE_MODULE_PATH ${module_path})
unset(module_path)

find_package(BaslerBlaze REQUIRED)

# add_executable(Sample test.cpp)
# target_link_libraries(FirstSample BaslerBlaze::BaslerBlazeSDK)


#=============================================



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
    # ${CMAKE_SOURCE_DIR}/ToF_camera
    )

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    stdc++fs
    pthread
    ${OpenCV_LIBS}
    camera
    BaslerBlaze::BaslerBlazeSDK
    # ToF_camera
    # YoloNet    
)