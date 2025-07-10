
#include "Token.h"

Token::Token(TokenType type, int start, int end, int line)
		: type(type), start(start), end(end), line(line) {

}

int Token::length() {
		return end - start;
}