cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
set(PROJECT_NAME zed_core)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option to generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the zed_core library (include your own source files here)
add_library(${PROJECT_NAME} STATIC
    src/core.cpp # Add your source files here
)

# Include the core's inc/ directory
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/inc # Add path to n.hpp
)

# Conditionally link to `zed_b` and `zed_n` if they don't already exist
if(NOT TARGET zed_b)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../utility ${CMAKE_BINARY_DIR}/utility)
endif()
if(NOT TARGET zed_n)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../common ${CMAKE_BINARY_DIR}/common)
endif()

# Link to `zed_b` and `zed_n`
target_link_libraries(${PROJECT_NAME} PRIVATE zed_b zed_n)

# Ensure `utility/inc/` and `common/inc/` are included for executables
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../utility/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/inc
)

# Macro for adding executables
macro(add_core_executable name)
    add_executable(${name}.out ${CMAKE_CURRENT_SOURCE_DIR}/tests/${name}.cpp)
    target_include_directories(${name}.out PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../utility/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/../common/inc # Include n.hpp for test executables
    )
    target_link_libraries(${name}.out ${PROJECT_NAME})
endmacro()

# Add test executables
add_core_executable(test_core)

# Print a message if compile_commands.json is generated
if (CMAKE_EXPORT_COMPILE_COMMANDS)
    message(STATUS "compile_commands.json will be generated in the build directory.")
endif()

