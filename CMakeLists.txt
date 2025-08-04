cmake_minimum_required(VERSION 3.28)
project(drakon
    LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
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
    src/drakon/game.cpp
    src/drakon/error.cpp
    src/drakon/event.cpp
    src/drakon/scene.cpp
    src/drakon/entity/entity.cpp
    src/drakon/component/component.cpp
    src/drakon/component/PrintComponent.cpp
    src/drakon/component/PositionComponent.cpp
    src/drakon/component/TextureComponent.cpp
    src/drakon/system/EventSystem.cpp
    src/drakon/system/PrintSystem.cpp
    src/drakon/system/TextureSystem.cpp
)

add_library(drakon SHARED STATIC
    ${SOURCE_FILES}
)

target_compile_options(
    drakon PRIVATE
    # C++ warnings
    $<$<COMPILE_LANGUAGE:CXX>:${COMPILER_FLAGS}>
)
target_compile_definitions(
    drakon PRIVATE
    DRAKON_SDL
)

target_include_directories(drakon PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3_image/include>
)

# [GLM] START
set(GLM_FORCE_CMAKE_VERSION ON CACHE BOOL "Override GLM's max CMake version policy")
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

add_subdirectory(vendor/glm SYSTEM)
target_link_libraries(drakon PRIVATE glm::glm)
# [GLM] END
# [SDL3] START
add_subdirectory(vendor/SDL3 SYSTEM)

target_link_libraries(drakon PRIVATE SDL3::SDL3)
## [SDL3_image] START
add_subdirectory(vendor/SDL3_image SYSTEM)

target_link_libraries(drakon PRIVATE SDL3_image::SDL3_image)
## [SDL3_image] END
# [SDL3] END
add_subdirectory(examples/hello EXCLUDE_FROM_ALL)
