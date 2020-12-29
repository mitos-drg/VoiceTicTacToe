# This is the top-most CMake file for VoiceChess project
cmake_minimum_required(VERSION 3.1)

# Start the VoiceChess project
project(VoiceTicTacToe CXX)

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
set_target_properties(sfml-graphics PROPERTIES FOLDER dependencies)

add_subdirectory(dep/sphinxbase)
set_target_properties(sphinxbase PROPERTIES FOLDER dependencies)
add_subdirectory(dep/pocketsphinx)
set_target_properties(pocketsphinx PROPERTIES FOLDER dependencies)


# Add project main executable
add_subdirectory(TicTacToe)