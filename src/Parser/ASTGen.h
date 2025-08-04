
#pragma once

#include <vector>
#include <memory>
#include <set>

#include "Token.h"
#include "Expr.h"

using namespace ExprOps;

class ASTGen {
public:
	ASTGen(const std::vector<unsigned char>&, const std::vector<Token>&);
public:
	std::vector<std::unique_ptr<Expr> > buildAST();
private:
	std::unique_ptr<Expr> orr();
	std::unique_ptr<Expr> andd();
	std::unique_ptr<Expr> equality();
	std::unique_ptr<Expr> comparison();
	std::unique_ptr<Expr> term();
	std::unique_ptr<Expr> factor();
	std::unique_ptr<Expr> unary();
	std::unique_ptr<Expr> primary();

	bool match(std::set<TokenType>);
	Token advance();
	Token previous();
	Token consume(TokenType, std::string_view);
	bool isAtEnd();

	double createDouble();
private:
	const std::vector<unsigned char> source;
	const std::vector<Token> tokens;

	int current = 0;

	std::vector<std::unique_ptr<Expr> > AST = {};
};