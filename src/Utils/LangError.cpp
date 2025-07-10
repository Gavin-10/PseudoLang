
#include "LangError.h"

namespace LangError
{
		void scanError(std::string_view message, int line) {
				std::cerr << "[line " << line << "]" << '\t' << "Parse Error" << '\t' << message << std::endl;

				exit(1);
		}
}