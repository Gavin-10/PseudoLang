
#pragma once

#include <stack>

#include "Value.h"
#include "Chunk.h"

using namespace ValueOps;
using namespace ChunkOps;

class VM {
public:
		enum class InterpretResult {
				INTERPRET_OK,
				PARSE_ERROR,
				RESOLVER_ERROR,
				RUNTIME_ERROR,
		};
public:
		VM(Chunk&);
public:
		InterpretResult interpret();
private:
	uint8_t readByte();
	Value pop();
	bool isFalsey(Value);
	void equality();
	int line();
private:
		std::stack<Value> stack = {};
		Chunk chunk;
		int chunkPos = 0;
};