cmake_minimum_required(VERSION 3.1)

project(camera)
list(APPEND CMAKE_PREFIX_PATH "/opt/MVS/lib/64/" "/opt/MVS/lib/aarch64/")

find_library(CAMERA_LIB MvCameraControl REQUIRED )   
find_package(OpenCV REQUIRED)

add_library(${PROJECT_NAME} 
    hik_vision.cpp
    )

target_include_directories(${PROJECT_NAME} 
    PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    /opt/MVS/include
    )

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${CAMERA_LIB}

    PRIVATE
    ${OpenCV_LIBS}
)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)