cmake_minimum_required(VERSION 3.28)
project(drakon
    LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(COMPILER_FLAGS
        -Wall
        -Werror # treat warnings as errors
        -Wextra # reasonable and standard
        -Wshadow # warn the user if a variable declaration shadows one from a parent context
        -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
        -Wpedantic # warn if non-standard C++ is used
        -pedantic-errors # treat non-standard C++ as an error
        # catch hard to track down memory errors
        -Wold-style-cast # warn for c-style casts
        -Wcast-align # warn for potential performance problem casts
        -Wunused # warn on anything being unused
        -Woverloaded-virtual # warn if you overload (not override) a virtual function
        -Wconversion # warn on type conversions that may lose data
        -Wsign-conversion # warn on sign conversions
        -Wnull-dereference # warn if a null dereference is detected
        -Wdouble-promotion # warn if float is implicit promoted to double
        -Wformat=2 # warn on security issues around functions that format output (ie printf)
        -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
        # GCC-specific
        -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
    )
set(SOURCE_FILES
    src/drakon.cpp
    src/drakon/game.cpp
    src/drakon/error.cpp
    src/drakon/system/eventsystem.cpp
)
add_library(drakon SHARED STATIC
    ${SOURCE_FILES}
)

target_compile_options(
    drakon PRIVATE
    # C++ warnings
    $<$<COMPILE_LANGUAGE:CXX>:${COMPILER_FLAGS}>
)

target_include_directories(drakon PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(drakon PRIVATE SDL3::SDL3)

add_subdirectory(vendor/SDL3 SYSTEM)
add_subdirectory(examples/hello EXCLUDE_FROM_ALL)
