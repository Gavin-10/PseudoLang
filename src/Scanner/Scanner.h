
#pragma once

#include <vector>
#include <string>
#include <string_view>

#include "Token.h"

class Scanner {
public:
		Scanner(std::vector<unsigned char>&);
public:
		std::vector<Token> scan();
private:
		inline void tokenGen(TokenType type) {
				tokens.emplace_back(type, start, current, line);
		}
private:

		void advance();
		void number();
		void string();
		void identifier();

		unsigned char peek();
		unsigned char peekNext();

		bool match(unsigned char);
		bool isAlpha(unsigned char);
		bool isDigit(unsigned char);
		bool isAlphaNum(unsigned char);
		bool sourceEnd();
private:
		std::vector<Token> tokens = {};
		std::vector<unsigned char> source;
		int start = 0;
		int current = 1;
		int line = 1;
};