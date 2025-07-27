cmake_minimum_required(VERSION 3.28)
project(drakon
    LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(SOURCE_FILES
    src/drakon.cpp
)
add_library(drakon SHARED STATIC
    ${SOURCE_FILES}
)

target_include_directories(drakon PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(drakon PRIVATE SDL3::SDL3)

add_subdirectory(vendor/SDL3)
add_subdirectory(examples/hello EXCLUDE_FROM_ALL)
