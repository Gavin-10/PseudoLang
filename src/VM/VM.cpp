
#include "VM.h"

#include <iostream>

#include "LangError.h"

using namespace ChunkOps;

VM::VM(Chunk& chunk) : chunk(chunk) {};

VM::InterpretResult VM::interpret() {
	if (chunk.code.size() == 0) {
		return InterpretResult::INTERPRET_OK;
	}

#define BINARY_OP(op) \
do { \
	double b = valueAs<double>(pop(), "Double", line()); \
	double a = valueAs<double>(pop(), "Double", line()); \
	stack.push(a op b); \
} while (false)

	while (true) {
		if (chunkPos >= chunk.code.size()) {
			std::cout << valueAs<double>(pop(), "Double", line()) << std::endl;
			return InterpretResult::INTERPRET_OK;
		}
		uint8_t instruction;
		switch (instruction = readByte()) {

		case uint8_t(OpCode::OP_NIL):
			stack.push(Value(nullptr));
			break;
		case uint8_t(OpCode::OP_TRUE):
			stack.push(Value(true));
			break;
		case uint8_t(OpCode::OP_FALSE):
			stack.push(Value(false));
			break;

		case uint8_t(OpCode::OP_POP):
			pop();
			break;
		case uint8_t(OpCode::OP_CONSTANT):
			stack.push(chunk.constants[readByte()]);
			break;

		case uint8_t(OpCode::OP_EQUAL): 
			stack.push(pop() == pop());
			break;
		case uint8_t(OpCode::OP_GREATER):
			BINARY_OP(> );
			break;
		case uint8_t(OpCode::OP_LESS):
			BINARY_OP(< );
			break;

		case uint8_t(OpCode::OP_ADD):
			BINARY_OP(+);
			break;
		case uint8_t(OpCode::OP_SUBTRACT):
			BINARY_OP(-);
			break;
		case uint8_t(OpCode::OP_MULTIPLY):
			BINARY_OP(*);
			break;
		case uint8_t(OpCode::OP_DIVIDE):
			BINARY_OP(/ );
			break;

		case uint8_t(OpCode::OP_NOT):
			stack.push(!isFalsey(pop()));
			break;
		case uint8_t(OpCode::OP_NEGATE):
			if (valueIs<double>(stack.top())) {
				stack.push(-valueAs<double>(pop(), "Double", line()));
			} else {
				LangError::runtimeError("Only numbers can be negated", line());
			}
			
			break;

		default:
			return InterpretResult::RUNTIME_ERROR;
		}
	}
}

uint8_t VM::readByte() {
	return chunk.code[chunkPos++];
}

Value VM::pop() {
	if (stack.empty()) {
		LangError::runtimeError("Stack Underflow", line());
		return nullptr;
	} else {
		Value top = stack.top();
		stack.pop();
		return top;
	}
}

bool VM::isFalsey(Value value) {
	if (valueIs<bool>(value)) {
		return valueAs<bool>(value, "Boolean", line());
	} else if (valueIs<nullptr_t>(value)) {
		return false;
	} else {
		return true;
	}
}

int VM::line() {
	return chunk.lines[chunkPos - 1];
}