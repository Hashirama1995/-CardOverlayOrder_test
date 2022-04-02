cmake_minimum_required(VERSION 3.18.0)

project(testProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


set(HEADERS 
    Image.h
    functions.h
    )

set(SOURCES
    Image.cpp
    functions.cpp
    )

add_executable(${PROJECT_NAME} main.cpp ${HEADERS} ${SOURCES})

set_target_properties(testProject PROPERTIES
                    CXX_STANDARD 11
                    CXX_STANDARD_REQUIRED ON                   
)