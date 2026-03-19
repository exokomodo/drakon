set(
    ALL_EXAMPLES
    hello
)

message("Examples to be built: ${ALL_EXAMPLES}")

set(GLSLC_EXECUTABLE "${Vulkan_GLSLC_EXECUTABLE}")
if(GLSLC_EXECUTABLE AND NOT IS_ABSOLUTE "${GLSLC_EXECUTABLE}")
    unset(GLSLC_EXECUTABLE)
endif()
if(NOT GLSLC_EXECUTABLE)
    find_program(
        GLSLC_EXECUTABLE
        NAMES glslc glslc.exe
        HINTS "$ENV{VULKAN_SDK}/Bin" "$ENV{VULKAN_SDK}/Bin32"
    )
endif()
if(NOT GLSLC_EXECUTABLE)
    message(FATAL_ERROR "Vulkan glslc not found. Ensure the Vulkan SDK is installed and VULKAN_SDK is set.")
endif()

foreach(example ${ALL_EXAMPLES})
    add_executable(examples.${example})
    set_property(TARGET examples.${example} PROPERTY CXX_STANDARD 20)
    target_sources(examples.${example} PRIVATE ${example}/main.cpp)
    target_link_libraries(
        examples.${example}
        PRIVATE
        exokomodo::drakon
    )
endforeach()

set(HELLO_SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/hello/shaders")
file(GLOB HELLO_SHADERS "${HELLO_SHADER_DIR}/*.vert" "${HELLO_SHADER_DIR}/*.frag")

set(HELLO_SPV)
foreach(shader IN LISTS HELLO_SHADERS)
    get_filename_component(shader_name "${shader}" NAME)
    set(spv "${CMAKE_CURRENT_BINARY_DIR}/hello/shaders/${shader_name}.spv")
    add_custom_command(
        OUTPUT "${spv}"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/hello/shaders"
        COMMAND "${GLSLC_EXECUTABLE}" -o "${spv}" "${shader}"
        DEPENDS "${shader}"
        VERBATIM
    )
    list(APPEND HELLO_SPV "${spv}")
endforeach()

add_custom_target(examples.hello.shaders DEPENDS ${HELLO_SPV})
add_dependencies(examples.hello examples.hello.shaders)
