
#include "CodeGen.h"

CodeGen::CodeGen(std::vector<std::unique_ptr<Expr> >&& AST) : AST(std::move(AST)) {};

std::unique_ptr<Chunk> CodeGen::generate() {
	chunk = std::make_unique<Chunk>();
	
	for (auto& expr : AST) {
		expr->accept(*this);
	}

	return std::move(chunk);
}

void CodeGen::visitTernaryExpr(const Ternary& expr) {

}

void CodeGen::visitBinaryExpr(const Binary& expr) {
	expr.left->accept(*this);
	expr.right->accept(*this);
	writeInstructionFromToken(expr.operatorr.type, expr.operatorr.line);
}

void CodeGen::visitGroupingExpr(const Grouping& expr) {
	expr.expression->accept(*this);
}

void CodeGen::visitLiteralExpr(const Literal& expr) {
	chunk->writeChunk(uint8_t(OpCode::OP_CONSTANT), expr.line);
	size_t index = chunk->addConstant(expr.value);
	chunk->writeChunk(index, expr.line);
}

void CodeGen::visitLogicalExpr(const Logical& expr) {

}

void CodeGen::visitUnaryExpr(const Unary& expr) {
	expr.right->accept(*this);
	if (expr.operatorr.type == BANG) {
		chunk->writeChunk(uint8_t(OpCode::OP_NOT), expr.operatorr.line);
	} else {
		chunk->writeChunk(uint8_t(OpCode::OP_NEGATE), expr.operatorr.line);
	}
}

void CodeGen::writeInstructionFromToken(TokenType type, int line) {
	switch (type) {
	case PLUS:
		chunk->writeChunk(uint8_t(OpCode::OP_ADD), line);
		break;
	case MINUS:
		chunk->writeChunk(uint8_t(OpCode::OP_SUBTRACT), line);
		break;
	case STAR:
		chunk->writeChunk(uint8_t(OpCode::OP_MULTIPLY), line);
		break;
	case SLASH:
		chunk->writeChunk(uint8_t(OpCode::OP_DIVIDE), line);
		break;
	case LESS:
		chunk->writeChunk(uint8_t(OpCode::OP_LESS), line);
		break;
	case GREATER:
		chunk->writeChunk(uint8_t(OpCode::OP_GREATER), line);
		break;
	case LESS_EQUAL:
		chunk->writeChunk(uint8_t(OpCode::OP_GREATER), line);
		chunk->writeChunk(uint8_t(OpCode::OP_NOT), line);
		break;
	case GREATER_EQUAL:
		chunk->writeChunk(uint8_t(OpCode::OP_LESS), line);
		chunk->writeChunk(uint8_t(OpCode::OP_NOT), line);
		break;
	case EQUAL_EQUAL:
		chunk->writeChunk(uint8_t(OpCode::OP_EQUAL), line);
		break;
	default:
		break;
	}
}
