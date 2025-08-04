
#pragma once

#include <string>
#include <string_view>
#include <iostream>

namespace LangError
{

		void scanError(std::string_view, int);

		void parseError(std::string_view, int);

		void valueAccessError(std::string_view, int);

		void runtimeError(std::string_view, int);
}