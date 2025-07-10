# CMakeList.txt : CMake project for PseudoLang, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("PseudoLang")

# Add source to this project's executable.
add_subdirectory("src")

add_executable (PseudoLang "PseudoLang.cpp" "src/AST/Expr.h" "src/AST/Expr.cpp")

target_link_libraries(PseudoLang PUBLIC Scanner)
target_link_libraries(PseudoLang PUBLIC LangError)
target_link_libraries(PseudoLang PUBLIC Parser)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PseudoLang PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
