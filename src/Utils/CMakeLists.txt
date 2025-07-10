
add_library(Values STATIC "Value.cpp")
target_include_directories(Values INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Objects STATIC "Object.cpp")
target_include_directories(Objects INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(LangError STATIC "LangError.cpp")
target_include_directories(LangError INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})