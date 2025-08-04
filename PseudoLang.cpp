// PseudoLang.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

#include "Scanner.h"
#include "ASTGen.h"
#include "Chunk.h"
#include "VM.h"
#include "Value.h"
#include "Expr.h"
#include "CodeGen.h"

using namespace ChunkOps;
using namespace ValueOps;
using namespace ExprOps;

void printTokens(std::vector<Token>& tokens, std::vector<unsigned char>& source) {
		for (Token token : tokens) {
				for (int i = 0; i < token.length(); i++) {
						std::cout << source.at(token.start + i);
				}
				std::cout << '\t' << token.type << std::endl;
				std::cout << std::endl;
		}
}

void repl() {
		std::cout << "running repl" << std::endl;
}

std::vector<unsigned char> openFile(std::string_view sourcePath) {
		std::ifstream file(std::string(sourcePath), std::ios::binary);
		if (file.is_open()) {
				std::string output = "";
				std::vector<unsigned char> out = {};

				while (!file.eof()) {
						out.push_back(file.get());
				}

				return out;
		}

		return {};
}

void run(std::string_view sourcePath) {
		std::vector<unsigned char> source = openFile(sourcePath);

		std::vector<Token> tokens = Scanner(source).scan();

#ifdef TOKEN_DEBUG
		printTokens(tokens, source);
#endif
		std::vector<std::unique_ptr<Expr> > AST = ASTGen(source, tokens).buildAST();
		std::unique_ptr<Chunk> primer = CodeGen(std::move(AST)).generate();

		VM(*primer).interpret();
}

int main(int argc, char* argv[]) {

		/*
		if (argc == 1) repl();
		else if (argc == 2) run(argv[1]);
		else {
				std::cerr << "Unexpected arguments...Usage: [PseudoLang (filename.txt)?]" << std::endl;
				exit(64);
		}
		*/

		run("C:/Projects/PseudoLang/input.txt");

		return 0;
}
