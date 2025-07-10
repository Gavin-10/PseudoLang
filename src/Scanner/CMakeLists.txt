add_library(Scanner Scanner.cpp TokenType.h Token.cpp)

target_link_libraries(Scanner PUBLIC LangError)
target_include_directories(Scanner INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

