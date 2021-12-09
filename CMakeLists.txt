# This is the top-most CMake file for VoiceChess project
cmake_minimum_required(VERSION 3.1)

# Start the VoiceChess project
project(VoiceTicTacToe CXX C)

# Global project settings

# Reduce the config types to only Debug and Release
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# Set project binary output (out of source)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

# Set project binary output (in source)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)

# Use folders in project
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# Add project dependencies
set(BUILD_SHARED_LIBS FALSE)
set(SFML_BUILD_NETWORK FALSE)
set(SFML_BUILD_AUDIO FALSE)
add_subdirectory(dep/sfml)

if (WIN32)
    add_subdirectory(dep/sphinxbase)
    set_target_properties(sphinxbase PROPERTIES FOLDER dependencies)
    set(SPHINXBASE sphinxbase)
    add_subdirectory(dep/pocketsphinx)
    set_target_properties(pocketsphinx PROPERTIES FOLDER dependencies)
    set(POCKETSPHINX pocketsphinx)
ELSE()
    find_library(SPHINXBASE sphinxbase REQUIRED)
    find_path(SPHINXBASEINCL sphinxbase.h)
    find_library(SPHINXAD sphinxad REQUIRED)
    find_library(POCKETSPHINX pocketsphinx REQUIRED)
    find_path(POCKETSPHINXINCL pocketsphinx.h)

    message(STATUS "SPHINXBASE path: ${SPHINXBASE}")
    message(STATUS "SPHINXBASE path: ${SPHINXBASEINCL}")
    message(STATUS "SPHINXAD path: ${SPHINXAD}")
    message(STATUS "POCKETSPHINX path: ${POCKETSPHINX}")
    message(STATUS "POCKETSPHINX path: ${POCKETSPHINXINCL}")
ENDIF()

# Add project main executable
add_subdirectory(TicTacToe)

# /usr/local/include/pocketsphinx/pocketsphinx_export.h