
add_library(Parser "ASTGen.cpp")

target_link_libraries(Parser PUBLIC Scanner)
target_link_libraries(Parser PUBLIC AST)

target_include_directories(Parser INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})