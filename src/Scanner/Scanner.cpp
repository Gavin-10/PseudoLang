
#include "Scanner.h"

#include <utility>
#include <iostream>
#include <unordered_map>
#include <string>

#include "LangError.h"

const std::unordered_map<std::string, TokenType> keywords =
{
		{"and", AND},
		{"class", CLASS},
		{"const", CONST},
		{"else", ELSE},
		{"flase", FALSE},
		{"func", FUNC},
		{"for", FOR},
		{"if", IF},
		{"nil", NIL},
		{"or", OR},
		{"print", PRINT},
		{"return", RETURN},
		{"super", SUPER},
		{"this", THIS},
		{"true", TRUE},
		{"var", VAR},
		{"while", WHILE},
		{"repeat", REPEAT},
		{"member", MEMBER},
		{"method", METHOD},
		{"constructor", CONSTRUCTOR},
		{"chain", CHAIN},
		{"with", WITH},
		{"break", BREAK}
};

Scanner::Scanner(std::vector<unsigned char>& source) : source(source) {};

std::vector<Token> Scanner::scan() {
		while (!sourceEnd()) {

				switch (source.at(start)) {
				case '\n':
						line++;
						break;
				case '\r':
						break;
				case '\t':
						break;
				case ' ':
						break;

				case '(': tokenGen(LEFT_PAREN); break;
				case ')': tokenGen(RIGHT_PAREN); break;
				case '{': tokenGen(LEFT_BRACE); break;
				case '}': tokenGen(RIGHT_BRACE); break;
				case '[': tokenGen(LEFT_BRACKET); break;
				case ']': tokenGen(RIGHT_BRACKET); break;
				case ',': tokenGen(COMMA); break;
				case '.': tokenGen(DOT); break;
				case ';': tokenGen(SEMICOLON); break;
				case '?': tokenGen(QUESTION); break;
				case ':': tokenGen(COLON); break;

				case '!': 
						match('=') ? tokenGen(BANG_EQUAL) : tokenGen(BANG);
						break;
				case '=':
						if (match('=')) {
								tokenGen(EQUAL_EQUAL);
						} else if (match('>')) {
								tokenGen(ARROW);
						} else {
								tokenGen(EQUAL);
						}
						break;
				case '>':
						match('=') ? tokenGen(GREATER_EQUAL) : tokenGen(GREATER);
						break;
				case '<':
						match('=') ? tokenGen(LESS_EQUAL) : tokenGen(LESS);
						break;
				case '-':
						match('=') ? tokenGen(MINUS_EQUAL) : tokenGen(MINUS);
						break;
				case '+':
						match('=') ? tokenGen(PLUS_EQUAL) : tokenGen(PLUS);
						break;
				case '*':
						match('=') ? tokenGen(STAR_EQUAL) : tokenGen(STAR);
						break;
				case '/':
						if (match('/')) {
								while (!match('\n')) advance();
								line++;
						} else if (match('*')) {
								while (!(match('*') && match('/'))) {
										if (peek() == '\n') line++;
										advance();
								}
						} else if (match('=')) {
								tokenGen(SLASH_EQUAL);
						} else {
								tokenGen(SLASH);
						}

						break;
				case '"':
						while (!sourceEnd() && !match('"')) advance();
						if (sourceEnd()) {
								LangError::scanError("Unterminated String", line);
						} else {
								tokens.emplace_back(STRING, start + 1, current - 1, line);
						}
						break;

				case 255:
						tokens.emplace_back(END_OF_FILE, start, start, line);
						break;


				default:
						if (isDigit(source.at(start))) {
								while (isDigit(source.at(current))) advance();
								if (match('.')) {
										advance();
										while (isDigit(source.at(current))) advance();
								}
								tokenGen(NUMBER);
						} else if(isAlpha(source.at(start))) {
								while (isAlphaNum(source.at(current))) advance();

								std::string combined;
								for (int i = start; i < current; i++) {
										combined += source.at(i);
								}

								if (keywords.contains(combined)) {
										tokenGen(keywords.at(combined));
								} else {
										tokenGen(IDENTIFIER);
								}
								
						} else {
								std::string error = "Unknown character encountered" + '\t' + source.at(start);
								LangError::scanError(error, line);
						}
				}

				start = current;
				advance();
		}

		return tokens;
}

void Scanner::advance() {
		current++;
}

unsigned char Scanner::peek() {
		if (!sourceEnd()) {
				return source.at(current);
		}

		return 255;
}

unsigned char Scanner::peekNext() {
		if (!(current >= source.size() + 1)) {
				return source.at(current + 1);
		}

		return 255;
}

bool Scanner::match(unsigned char expected) {
		if (peek() == expected) {
				advance();
				return true;
		} else {
				return false;
		}
}

bool Scanner::isAlpha(unsigned char tested) {
		return (tested >= 'a' && tested <= 'z') || (tested >= 'A' && tested <= 'Z');
}

bool Scanner::isDigit(unsigned char tested) {
		return tested >= '0' && tested <= '9';
}

bool Scanner::isAlphaNum(unsigned char tested) {
		return tested == '_' || isAlpha(tested) || isDigit(tested);
}

bool Scanner::sourceEnd() {
		return current >= source.size();
}