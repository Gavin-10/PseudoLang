
#pragma once

#include "TokenType.h"

struct Token {
		Token(TokenType, int, int, int);

		int length();

		const TokenType type;
		const int start;
		const int end;
		const int line;
};