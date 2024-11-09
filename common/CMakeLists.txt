cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
set(PROJECT_NAME zed_n)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option to generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include the /inc directory for the library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:include>
)

# Macro for adding test executables
macro(add_test_executable name)
    add_executable(${name}.out tests/${name}.cpp)
    target_link_libraries(${name}.out ${PROJECT_NAME})
endmacro()

# Add test executables
add_test_executable(test_n)

# Optional: Print a message if compile_commands.json is generated
if (CMAKE_EXPORT_COMPILE_COMMANDS)
    message(STATUS "compile_commands.json will be generated in the build directory.")
endif()

