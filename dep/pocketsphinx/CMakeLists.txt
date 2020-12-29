# Get all project files
file(GLOB_RECURSE sourceDir ${CMAKE_CURRENT_SOURCE_DIR}/source/*)

# Add pocketsphinx library
add_library (pocketsphinx ${sourceDir})
set_target_properties(pocketsphinx PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories (pocketsphinx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_include_directories (pocketsphinx PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/pocketsphinx/)

target_link_libraries (pocketsphinx LINK_PUBLIC sphinxbase)
# target_link_libraries (LINK_PUBLIC PocketSphinx)