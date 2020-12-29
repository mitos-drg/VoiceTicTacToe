# Get all project files
file(GLOB_RECURSE sourceDir ${CMAKE_CURRENT_SOURCE_DIR}/source/*)

# Add sphinxbase library
add_library (sphinxbase ${sourceDir})
set_target_properties(sphinxbase PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories (sphinxbase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)