cmake_minimum_required(VERSION 3.10)

# Top-level project name
project(zed)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS ON)

# Set CMP0079 policy to NEW for target_link_libraries
if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()

# Option to generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add subdirectories in the correct order
add_subdirectory(common)
add_subdirectory(utility)
add_subdirectory(core)

# Ensure `zed_b` links to `zed_n` only if both exist
if(TARGET zed_n AND TARGET zed_b)
    target_link_libraries(zed_b INTERFACE zed_n)
endif()

# Ensure `zed_core` links to `zed_n` and `zed_b` only if all exist
if(TARGET zed_core AND TARGET zed_n AND TARGET zed_b)
    target_link_libraries(zed_core PRIVATE zed_n zed_b)
endif()

# Custom target to clean all `build` directories
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR} ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/build
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/core/build
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/common/build
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/utility/build
    COMMENT "Removing all build directories: root, core/build, common/build, utility/build"
)

