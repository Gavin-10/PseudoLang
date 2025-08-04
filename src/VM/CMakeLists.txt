add_library(VM "VM.cpp" "Chunk.cpp")

target_link_libraries(VM PUBLIC Utils)
target_include_directories(VM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})