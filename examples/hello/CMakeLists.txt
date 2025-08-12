cmake_minimum_required(VERSION 3.28)
project(hello
    LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_executable(hello WIN32 main.cpp)
target_compile_definitions(hello PRIVATE
    DRAKON_SDL
)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    # NOTE: Enable sanitizers for debugging memory issues
    target_compile_options(hello PRIVATE -fsanitize=address -fno-omit-frame-pointer)
    target_link_options(hello PRIVATE -fsanitize=address)
endif()
target_link_libraries(hello PRIVATE drakon SDL3::SDL3 SDL3_image::SDL3_image)

