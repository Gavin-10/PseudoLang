
#include "LangError.h"

namespace LangError
{
		void scanError(std::string_view message, int line) {
				std::cerr << "[line " << line << "]" << '\t' << "Lexer Error:" << '\t' << message << std::endl;

				exit(1);
		}

		void parseError(std::string_view message, int line) {
			std::cerr << "[line " << line << "]" << '\t' << "Parse Error:" << '\t' << message << std::endl;
		}

		void valueAccessError(std::string_view type, int line) {
			std::string message = std::string("Value cast fail to ").append(type);
			runtimeError(message, line);
		}

		void runtimeError(std::string_view message, int line) {
			std::cerr << "[line " << line << "]" << "\t" << "Runtime Error:" << "\t" << message << std::endl;

			exit(1);
		}
}