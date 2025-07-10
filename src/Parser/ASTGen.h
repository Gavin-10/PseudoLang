
#pragma once

#include <vector>
#include <memory>

#include "Token.h"
#include "Expr.h"

class ASTGen {
public:
		ASTGen(const std::vector<unsigned char>&, const std::vector<Token>);
public:
		std::vector<std::unique_ptr<Expr::Expr> > parse();
private:
		std::unique_ptr<Expr::Expr> orr();
		std::unique_ptr<Expr::Expr> andd();
		std::unique_ptr<Expr::Expr> equality();
		std::unique_ptr<Expr::Expr> comparison();
		std::unique_ptr<Expr::Expr> term();
		std::unique_ptr<Expr::Expr> factor();
		std::unique_ptr<Expr::Expr> unary();
		std::unique_ptr<Expr::Expr> primary();
private:
		const std::vector<unsigned char> source;
		const std::vector<Token> tokens;

		std::vector<std::unique_ptr<Expr::Expr> > AST = {};
};