
add_library(Utils "Value.cpp" "Value.h" "LangError.cpp" "LangError.h" "Object.cpp" "Object.h")
target_include_directories(Utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})