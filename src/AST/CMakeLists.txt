
add_library(AST "Expr.cpp")

target_link_libraries(AST PUBLIC Scanner)
target_link_libraries(AST PUBLIC Utils)

target_include_directories(AST INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})