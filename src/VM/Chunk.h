
#pragma once

#include <vector>

#include "Value.h"

using namespace ValueOps;

namespace ChunkOps {
		enum class OpCode : uint8_t {
				OP_NIL,
				OP_TRUE,
				OP_FALSE,

				OP_POP,

				OP_CONSTANT,

				OP_EQUAL,
				OP_GREATER,
				OP_LESS,

				OP_ADD,
				OP_SUBTRACT,
				OP_MULTIPLY,
				OP_DIVIDE,

				OP_NOT,
				OP_NEGATE,

		};

		struct Chunk {
				std::vector<uint8_t> code = {};
				std::vector<Value> constants = {};
				std::vector<int> lines = {};
				
				void writeChunk(uint8_t, int);
				size_t addConstant(Value);
		};
}