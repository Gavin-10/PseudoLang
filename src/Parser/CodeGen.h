
#pragma once

#include <vector>
#include <memory>

#include "Expr.h"
#include "Chunk.h"

using namespace ExprOps;
using namespace ChunkOps;

class CodeGen : Visitor {
public:
	CodeGen(std::vector<std::unique_ptr<Expr> >&&);
public:
	std::unique_ptr<Chunk> generate();
private:
	void visitTernaryExpr(const Ternary& expr) override;
	void visitBinaryExpr(const Binary& expr) override;
	void visitGroupingExpr(const Grouping& expr) override;
	void visitLiteralExpr(const Literal& expr) override;
	void visitLogicalExpr(const Logical& expr) override;
	void visitUnaryExpr(const Unary& expr) override;

	void writeInstructionFromToken(TokenType, int);
private:
	const std::vector<std::unique_ptr<Expr> > AST;
	std::unique_ptr<Chunk> chunk;
};