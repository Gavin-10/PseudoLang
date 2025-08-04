
#include "ASTGen.h"

using namespace ExprOps;

ASTGen::ASTGen(const std::vector<unsigned char>& source, const std::vector<Token>& tokens) 
	: source(source), tokens(tokens) {
};

std::vector<std::unique_ptr<Expr> > ASTGen::buildAST() {
	while (!isAtEnd()) {
		AST.emplace_back(equality());
	}

	return std::move(this->AST);
}

std::unique_ptr<Expr> ASTGen::orr() {

	return andd();
}

std::unique_ptr<Expr> ASTGen::andd() {

	return equality();
}

std::unique_ptr<Expr> ASTGen::equality() {
	std::unique_ptr<Expr> expr = comparison();
	
	while (match({ BANG_EQUAL, EQUAL_EQUAL })) {
		Token operatorr = previous();
		std::unique_ptr<Expr> right = comparison();
		expr = std::make_unique<Binary>(std::move(expr), operatorr, std::move(right));
	}

	return expr;
}

std::unique_ptr<Expr> ASTGen::comparison() {
	std::unique_ptr<Expr> expr = term();

	while (match({ GREATER, GREATER_EQUAL, LESS, LESS_EQUAL })) {
		Token operatorr = previous();
		std::unique_ptr<Expr> right = term();
		expr = std::make_unique<Binary>(std::move(expr), operatorr, std::move(right));
	}

	return expr;
}

std::unique_ptr<Expr> ASTGen::term() {
	std::unique_ptr<Expr> expr = factor();

	while (match({ MINUS, PLUS })) {
		Token operatorr = previous();
		std::unique_ptr<Expr> right = factor();
		expr = std::make_unique<Binary>(std::move(expr), operatorr, std::move(right));
	}

	return expr;
}

std::unique_ptr<Expr> ASTGen::factor() {
	std::unique_ptr<Expr> expr = unary();

	while (match({ SLASH, STAR })) {
		Token operatorr = previous();
		std::unique_ptr<Expr> right = unary();
		expr = std::make_unique<Binary>(std::move(expr), operatorr, std::move(right));
	}

	return expr;
}

std::unique_ptr<Expr> ASTGen::unary() {
	if (match({ BANG, MINUS })) {
		Token operatorr = previous();
		std::unique_ptr<Expr> right = unary();
		return std::make_unique<Unary>(operatorr, std::move(right));
	}

	return primary();
}

std::unique_ptr<Expr> ASTGen::primary() {
	if (match({ FALSE })) return std::make_unique<Literal>(false, previous().line);
	if (match({ TRUE })) return std::make_unique<Literal>(true, previous().line);
	if (match({ NIL })) return std::make_unique<Literal>(nullptr, previous().line);

	if (match({ NUMBER })) return std::make_unique<Literal>(createDouble(), previous().line);

	if (match({ LEFT_PAREN })) {
		std::unique_ptr<Expr> expr = equality();
		consume(RIGHT_PAREN, "Expect ')' after expression.");
		return std::make_unique<Grouping>(std::move(expr));
	}

	LangError::parseError("Expression expected", tokens[current].line);
	advance();
}

bool ASTGen::match(std::set<TokenType> types) {
	if (!isAtEnd() && types.contains(tokens[current].type)) {
		advance();
		return true;
	}
	
	return false;
}

Token ASTGen::advance() {
	current++;
	return tokens[current - 1];
}

Token ASTGen::previous() {
	return tokens[current - 1];
}

Token ASTGen::consume(TokenType type, std::string_view message) {
	if (!isAtEnd() && tokens[current].type == type) return advance();

	LangError::parseError(message, tokens[current - 1].line);
}

bool ASTGen::isAtEnd() {
	return current >= tokens.size();
}

double ASTGen::createDouble() {
	Token numberToken = previous();
	std::string numberString = "";

	for (int i = 0; i < numberToken.length(); i++) {
		numberString += source[numberToken.start + i];
	}

	return std::stod(numberString);
}
