
add_library(Parser "ASTGen.cpp" "CodeGen.cpp")

target_link_libraries(Parser PUBLIC Scanner)
target_link_libraries(Parser PUBLIC AST)
target_link_libraries(Parser PUBLIC Utils)
target_link_libraries(Parser PUBLIC VM)

target_include_directories(Parser INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})